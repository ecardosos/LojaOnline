#include "Data\Order.h"

#include <cassert>

#include "Data\Address.h"
#include "Data\Product.h"

unsigned int Order::s_globalId = 0;

Order::Order(const char* orderDate, const IAddress* shippingAddress, float orderValue)
{
  assert(orderDate && std::strlen(orderDate) != 0);
  assert(shippingAddress);

  _orderId = s_globalId;

  _orderDate = orderDate;
  _shippingAddress = shippingAddress;
  _orderValue = orderValue;

  s_globalId++;
}

Order::~Order()
{
  delete _shippingAddress;
  // Product pointers are owned by their sections.
  _orderItems.clear();
}

unsigned int Order::getOrderId() const
{
  return _orderId;
}

const char* Order::getDate() const
{
  return _orderDate.c_str();
}

const IAddress* Order::getShippingAddress() const
{
  return _shippingAddress;
}

float Order::getTotal() const
{
  return _orderValue;
}

void Order::addItem(const IProduct* product)
{
  if (product != nullptr)
  {
    _orderItems.push_back(product);
  }
}

Order& Order::operator+=(const Order& o)
{
  _orderValue += o._orderValue;
  _orderId = s_globalId;
  s_globalId++;

  for (int i = 0; i < _orderItems.size(); i++)
  {
    _orderItems.push_back(o._orderItems.at(i));
  }

  return *this;
}

const std::vector<const IProduct*> Order::getItems() const
{
  return _orderItems;
}

std::ostream& operator<<(std::ostream& os, const Order* o)
{
  os << "Order date: " << o->getDate() << std::endl
     << "Products in this order:" << std::endl;

  std::vector<const IProduct*> products = o->getItems();
  for (unsigned int i = 0; i < products.size(); i++)
  {
    os << std::endl
       << dynamic_cast<const Product*>(products.at(i)) << std::endl;
  }

  os << std::endl
     << "Order value: US$" << o->getTotal() << std::endl;

  os << std::endl
     << "Shipping address:" << std::endl << std::endl
     << dynamic_cast<const Address*>(o->getShippingAddress());

  return os;
}