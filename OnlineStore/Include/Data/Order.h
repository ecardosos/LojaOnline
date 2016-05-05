#pragma once

#include "Interfaces\Data\IOrder.h"

class Order : public IOrder
{
  friend std::ostream& operator<<(std::ostream& os, const Order* o);

public:
  Order(const char* orderDate, const IAddress* shippingAddress, float orderValue);
  ~Order();

  // Returns the order id.
  unsigned int getOrderId() const override;

  // Returns the order date.
  const char* getDate() const override;

  // Returns the shipping address.
  const IAddress* getShippingAddress() const override;

  // Returns the order total value.
  float getTotal() const override;

  // Adds an item to this order.
  // Note: New items can only be added if the order is open.
  void addItem(const IProduct* product) override;

  // Returns the list of items in this order.
  const std::vector<const IProduct*> getItems() const override;

  //Operator+= overloading;
  Order& Order::operator+=(const Order& o);

  // Forbidden methods.
  Order()                        = delete;
  Order(const Order& o)          = delete;
  void operator=(const Order& o) = delete;

private:
  static unsigned int s_globalId;

  unsigned int _orderId;
  std::string _orderDate;
  const IAddress* _shippingAddress;
  float _orderValue;
  std::vector<const IProduct*> _orderItems;
};