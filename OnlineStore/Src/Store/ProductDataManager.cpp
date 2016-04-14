#include "Store\ProductDataManager.h"

#include <string>

#include "Interfaces\Data\IProduct.h"
#include "Interfaces\Data\ISection.h"

ProductDataManager::ProductDataManager()
{

}

ProductDataManager::~ProductDataManager()
{
  _productSections.clear();
}

void ProductDataManager::addSection(ISection* newSection)
{
  if (newSection != nullptr)
  {
    _productSections.push_back(newSection);
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

void ProductDataManager::addItemToSection(const char* sectionName, IProduct* newProduct)
{
  ISection* s = _getSectionByName(sectionName);

  if (s != nullptr)
  {
    s->addProduct(newProduct);
  }
}

const std::vector<IProduct*> ProductDataManager::getProductsForSection(const char* sectionName) const
{
  ISection* s = _getSectionByName(sectionName);

  if (s != nullptr)
  {
    return s->getProducts();
  }

  // TODO: Verify this return, might cause a crash.
  return std::vector<IProduct*>();
}

void ProductDataManager::addItemToStock(const char* sectionName, unsigned int productId, unsigned int amount)
{
  ISection* s = _getSectionByName(sectionName);

  if (s != nullptr)
  {
    IProduct* p = s->getProduct(productId);
    if (p != nullptr)
    {
      p->addItemsToStock(amount);
    }
  }
}

void ProductDataManager::removeItemFromStock(const char* sectionName, unsigned int productId, unsigned int amount)
{
  ISection* s = _getSectionByName(sectionName);

  if (s != nullptr)
  {
    IProduct* p = s->getProduct(productId);
    if (p != nullptr)
    {
      p->removeItemsFromStock(amount);
    }
  }
}

int ProductDataManager::getProductStock(const char* sectionName, unsigned int productId) const
{
  ISection* s = _getSectionByName(sectionName);

  if (s != nullptr)
  {
    IProduct* p = s->getProduct(productId);
    if (p != nullptr)
    {
      return static_cast<unsigned int>(p->getItemStock());
    }
  }

  // Error: Item not found.
  return -1;
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