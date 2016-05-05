#pragma once

#include <vector>

class IAddress;
class IOrder;

// Contains user-related data, such as name, date of birth, list of orders, etc.
class IUser
{
public:
  virtual ~IUser() {}

  // Returns the user login.
  virtual const char* getLogin() const = 0;

  // Sets the user password.
  virtual void setPassword(const char* password) = 0;

  // Returns the user password.
  virtual const char* getPassword() const = 0;

  // Returns the user name.
  virtual const char* getName() const = 0;

  // Adds an user address.
  // Note: For the sake of simplicity, only one address will be stored. New addresses will overwrite the previous one.
  virtual void addAddress(IAddress* newAddress) = 0;

  // Returns the registered address for this user.
  virtual IAddress* getAddress() const = 0;

  // Adds an order to the order history of this user.
  virtual void addOrder(IOrder* order) = 0;

  // Gets an user order by its id.
  virtual IOrder* getOrder(unsigned int orderId) const = 0;

  // Gets the list of orders made by this user.
  virtual const std::vector<IOrder*> getOrders() const = 0;
};