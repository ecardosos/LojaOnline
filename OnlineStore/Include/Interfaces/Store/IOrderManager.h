#pragma once

class IOrder;

// Stores information about all orders made by users.
class IOrderManager
{
public:
  virtual ~IOrderManager() {}

  // Closes and adds an order placed by the user.
  virtual void addOrder(const IOrder* order) = 0;

  // Returns an order given its id.
  virtual const IOrder* getOrder(unsigned int orderId) const = 0;

  // Returns the id of the last order made by the user.
  // Note: Returns std::numeric_limits<unsigned int>::max() if no order has been made yet.
  virtual unsigned int getLastOrderId() const = 0;
};