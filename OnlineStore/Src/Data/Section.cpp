#include "Data\Section.h"

#include <cassert>
#include <random>

#include "Interfaces\Data\IProduct.h"

Section::Section(const char* name)
{
  assert(name != nullptr);

  _name = name;
  _onSale = false;
}

Section::~Section()
{
  for (unsigned int i = 0; i < _products.size(); i++)
  {
    delete _products.at(i);
  }
  _products.clear();
}

void Section::setName(const char* name)
{
  assert(name);

  _name = name;
}

const char* Section::getName() const
{
  return _name.c_str();
}

void Section::addProduct(IProduct* product)
{
  if (product == nullptr)
  {
    return;
  }

  _products.push_back(product);
}

std::vector<IProduct*> Section::getProducts() const
{
  return _products;
}

IProduct* Section::getProduct(unsigned int productId) const
{
  for (unsigned int i = 0; i < _products.size(); i++)
  {
    IProduct* p = _products.at(i);
    if (productId == p->getProductId())
    {
      return p;
    }
  }

  // Error: Product not found.
  return nullptr;
}

void Section::setOnSale(bool onSale, float min, float max)
{
  if (min > max || min < 0.0f ||
      max < min || max > 1.0f )
  {
    return;
  }

  for (unsigned int i = 0; i < _products.size(); i++)
  {
    IProduct* p = _products.at(i);
    p->setOnSale(onSale);

    // Apply randomly calculated discount in between the given interval.
    if (onSale)
    {
      p->setDiscount(_calculateDiscount(min, max));
    }
    else
    {
      p->setDiscount(0.0f);
    }
  }
}

bool Section::onSale() const
{
  return _onSale;
}

// Modern C++ approach for generating random numbers within a range.
float Section::_calculateDiscount(float min, float max)
{
  std::random_device rd; // Obtain a random number from hardware
  std::mt19937 eng(rd()); // Seed the generator
  std::uniform_real_distribution<> distr(min, max); // Define the range.

  return static_cast<float>(distr(eng));
}