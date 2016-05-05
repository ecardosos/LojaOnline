#pragma once

#include "Interfaces\Data\IUser.h"

#include <string>

class User : public IUser
{
public:
  User(const char* login, const char* password, const char* name);

  // Returns the user login.
  const char* getLogin() const override;

  // Sets the user password.
  void setPassword(const char* password) override;

  // Returns the user password.
  const char* getPassword() const override;

  // Returns the user name.
  const char* getName() const override;

  // Adds an user address.
  // Note: For the sake of simplicity, only one address will be stored. New addresses will overwrite the previous one.
  void addAddress(IAddress* newAddress) override;

  // Returns the registered address for this user.
  IAddress* getAddress() const override;

  // Adds an order to the order history of this user.
  void addOrder(IOrder* order) override;

  // Gets an user order by its id.
  IOrder* getOrder(unsigned int orderId) const override;

  // Gets the list of orders made by this user.
  const std::vector<IOrder*> getOrders() const override;

private:
  std::string _userLogin;
  std::string _password;
  std::string _name;

  IAddress* _address;
  IOrder* _order;
};