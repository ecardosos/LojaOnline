#pragma once

#include <vector>

class IAddress;
class IProduct;

// Contains data about a specific closed order.
class IOrder
{
public:
  virtual ~IOrder() {}

  // Returns the order id.
  virtual unsigned int getOrderId() const = 0;

  // Returns the order date.
  virtual const char* getDate() const = 0;

  // Returns the shipping address.
  virtual const IAddress* getShippingAddress() const = 0;

  // Returns the order total value.
  virtual float getTotal() const = 0;

  // Adds an item to this order.
  // Note: New items can only be added if the order is open.
  virtual void addItem(const IProduct* product) = 0;

  // Returns the list of items in this order.
  virtual const std::vector<const IProduct*> getItems() const = 0;
};