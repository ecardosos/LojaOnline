#pragma once

#include "Interfaces\Store\IOrderManager.h"

#include <vector>

class OrderManager : public IOrderManager
{
public:
  OrderManager();
  ~OrderManager();

  // Closes and adds an order placed by the user.
  virtual void addOrder(const IOrder* order) override;

  // Returns an order given its id.
  const IOrder* getOrder(unsigned int orderId) const override;

  // Returns the id of the last order made by the user.
  // Note: Returns std::numeric_limits<unsigned int>::max() if no order has been made yet.
  unsigned int getLastOrderId() const override;

  // Forbidden methods.
  OrderManager(const OrderManager& m)   = delete;
  void operator=(const OrderManager& m) = delete;

private:
  std::vector<const IOrder*> _orders;
  unsigned int _lastOrderId;
};