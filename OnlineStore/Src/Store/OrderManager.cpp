#include "Store\OrderManager.h"

#include "Interfaces\Data\IOrder.h"

OrderManager::OrderManager()
{
  _lastOrderId = std::numeric_limits<unsigned int>::max();
}

OrderManager::~OrderManager()
{
  for (unsigned int i = 0; i < _orders.size(); i++)
  {
    delete _orders.at(i);
  }
  _orders.clear();
}

void OrderManager::addOrder(const IOrder* order)
{
  if (order == nullptr)
  {
    return;
  }

  _orders.push_back(order);
  _lastOrderId = order->getOrderId();
}

const IOrder* OrderManager::getOrder(unsigned int orderId) const
{
  for (unsigned int i = 0; i < _orders.size(); i++)
  {
    const IOrder* o = _orders.at(i);
    if (orderId == o->getOrderId())
    {
      return o;
    }
  }

  // Error: Order not found.
  throw std::invalid_argument("Invalid order id.");
}

unsigned int OrderManager::getLastOrderId() const
{
  return _lastOrderId;
}