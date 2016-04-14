#pragma once

#include <vector>

class IProduct;

// Contains data about a specific closed order.
class IOrder
{
public:
  virtual ~IOrder() {}

  // Returns the order date.
  virtual const char* getDate() const = 0;

  // Returns the order total value.
  virtual float getTotal() const = 0;

  // Returns the list of items in this order.
  virtual const std::vector<IProduct*> getItems() const = 0;
};