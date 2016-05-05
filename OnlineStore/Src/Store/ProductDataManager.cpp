#include "Store\ProductDataManager.h"

#include <string>

#include "Interfaces\Data\IProduct.h"
#include "Interfaces\Data\ISection.h"

ProductDataManager::ProductDataManager()
{

}

ProductDataManager::~ProductDataManager()
{
  for (unsigned int i = 0; i < _productSections.size(); i++)
  {
    delete _productSections.at(i);
  }
  _productSections.clear();

  // Product pointers are owned by their sections.
  _cart.clear();
}

void ProductDataManager::addSection(ISection* section)
{
  if (section != nullptr)
  {
    _productSections.push_back(section);
  }
}

const std::vector<const char*> ProductDataManager::getSectionList() const
{
  std::vector<const char*> sectionNames;
  for (unsigned int i = 0; i < _productSections.size(); i++)
  {
    ISection* s = _productSections.at(i);
    sectionNames.push_back(s->getName());
  }

  return sectionNames;
}

void ProductDataManager::addProductToSection(const char* sectionName, IProduct* product)
{
  if (product == nullptr)
  {
    throw std::invalid_argument("Invalid product.");
  }

  ISection* s = _getSectionByName(sectionName);
  if (s == nullptr)
  {
    throw std::invalid_argument("Invalid section name.");
  }

  s->addProduct(product);
}

const IProduct* ProductDataManager::getProduct(unsigned int productId) const
{
  for (unsigned int i = 0; i < _productSections.size(); i++)
  {
    IProduct* p = _productSections.at(i)->getProduct(productId);
    if (p != nullptr)
    {
      return p;
    }
  }

  throw std::invalid_argument("Invalid product id.");
}

const std::vector<IProduct*> ProductDataManager::getProductsForSection(const char* sectionName) const
{
  ISection* s = _getSectionByName(sectionName);
  if (s == nullptr)
  {
    throw std::invalid_argument("Invalid section name.");
  }

  return s->getProducts();
}

void ProductDataManager::addItemsToStock(const char* sectionName, unsigned int productId, unsigned int amount)
{
  ISection* s = _getSectionByName(sectionName);
  if (s == nullptr)
  {
    throw std::invalid_argument("Invalid section name.");
  }

  IProduct* p = s->getProduct(productId);
  if (p == nullptr)
  {
    throw std::invalid_argument("Invalid product id.");
  }

  p->addItemsToStock(amount);
}

void ProductDataManager::removeItemsFromStock(const char* sectionName, unsigned int productId, unsigned int amount)
{
  ISection* s = _getSectionByName(sectionName);
  if (s == nullptr)
  {
    throw std::invalid_argument("Invalid section name.");
  }

  IProduct* p = s->getProduct(productId);
  if (p == nullptr)
  {
    throw std::invalid_argument("Invalid product id.");
  }

  p->removeItemsFromStock(amount);
}

unsigned int ProductDataManager::getProductStock(const char* sectionName, unsigned int productId) const
{
  ISection* s = _getSectionByName(sectionName);
  if (s == nullptr)
  {
    throw std::invalid_argument("Invalid section name.");
  }

  IProduct* p = s->getProduct(productId);
  if (p == nullptr)
  {
    throw std::invalid_argument("Invalid product id.");
  }

  return p->getItemStock();
}

void ProductDataManager::addProductToCart(IProduct* product, unsigned int quantity)
{
  if (product == nullptr)
  {
    throw std::invalid_argument("Invalid product.");
  }
    
  if(quantity > 0)
  {
    for (unsigned int i = 0; i < _cart.size(); i++)
    {
      IProduct* p = _cart.at(i).first;
      if (p->getProductId() == product->getProductId())
      {
        _cart.at(i).second += quantity;
        return;
      }
    }

    _cart.push_back(std::pair<IProduct*, unsigned int>(product, quantity));
  }
}

void ProductDataManager::removeProductFromCart(IProduct* product)
{
  if (product == nullptr)
  {
    throw std::invalid_argument("Invalid product.");
  }

  // Iterates through the vector and remove the product, if it is found.
  std::vector<std::pair<IProduct*, unsigned int>>::iterator it;
  for (it = _cart.begin(); it != _cart.end(); it++)
  {
    if (it->first->getProductId() == product->getProductId())
    {
      // Remove one item from the cart.
      it->second -= 1;

      // Removes the item entirely if there are no items left.
      if (it->second <= 0)
      {
        _cart.erase(it);
      }
      return;
    }
  }
}

void ProductDataManager::removeAllItemsFromCart()
{
  _cart.clear();
}

std::vector<std::pair<IProduct*, unsigned int>> ProductDataManager::getProductsInCart() const
{
  return _cart;
}

float ProductDataManager::getTotalCartValue() const
{
  float total = 0.0f;

  for (unsigned int i = 0; i < _cart.size(); i++)
  {
    IProduct* p = _cart.at(i).first;
    total += p->getDiscountedPrice() * _cart.at(i).second;
  }

  return total;
}

ISection* ProductDataManager::_getSectionByName(const char* sectionName) const
{
  if (sectionName == nullptr)
  {
    return nullptr;
  }

  for (unsigned int i = 0; i < _productSections.size(); i++)
  {
    ISection* s = _productSections.at(i);
    if (std::strcmp(sectionName, s->getName()) == 0)
    {
      return s;
    }
  }

  // Error: Section not found.
  return nullptr;
}