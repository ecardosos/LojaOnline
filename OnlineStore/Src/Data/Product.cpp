#include "Data\Product.h"

#include <cassert>
#include <iomanip>

unsigned int Product::s_globalId = 0;

Product::Product(const char* name, const char* description, const char* manufacturer, float initialPrice, unsigned int initialStock)
{
  assert(name != nullptr);
  assert(description != nullptr);
  assert(manufacturer != nullptr);

  _name = name;
  _description = description;
  _manufacturer = manufacturer;
  _price = initialPrice;
  _itemStock = initialStock;
  _onSale = false;
  _discount = 0.0f;
  _productId = s_globalId;

  s_globalId++;
}

void Product::setName(const char* name)
{
  assert(name);

  _name = name;
}

const char* Product::getName() const
{
  return _name.c_str();
}

unsigned int Product::getProductId() const
{
  return _productId;
}

void Product::setDescription(const char* description)
{
  assert(description);

  _description = description;
}

const char* Product::getDescription() const
{
  return _description.c_str();
}

void Product::setManufacturer(const char* manufacturer)
{
  assert(manufacturer);

  _manufacturer = manufacturer;
}

const char* Product::getManufacturer() const
{
  return _manufacturer.c_str();
}

void Product::setPrice(float price)
{
  _price = price;
}

float Product::getPrice() const
{
  return _price;
}

float Product::getDiscountedPrice() const
{
  return _onSale ? (_price - _price * _discount) : _price;
}

void Product::setOnSale(bool onSale)
{
  _onSale = onSale;
}

bool Product::onSale() const
{
  return _onSale;
}

void Product::setDiscount(float discount)
{
  _discount = discount;
}

float Product::getDiscount() const
{
  return _discount;
}

void Product::addItemsToStock(unsigned int amount)
{
  _itemStock += amount;
}

void Product::removeItemsFromStock(unsigned int amount)
{
  _itemStock -= amount;
}

unsigned int Product::getItemStock() const
{
  return _itemStock;
}

std::ostream& operator<<(std::ostream& os, const Product* product)
{
  // Display only two decimal digits.
  os << std::setprecision(2) << std::fixed;

  os << product->getName() << " (" << product->getManufacturer() << ")" << std::endl
     << product->getDescription() << std::endl
     << "Price: US$ " << product->getDiscountedPrice();

  // Discount information is only added if product is on sale.
  if (product->onSale())
  {
    os << " (" << (product->getDiscount()) * 100.0f << "% OFF of US$ " << product->getPrice() << ")";
  }

  return os;
}