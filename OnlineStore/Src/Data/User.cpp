#include "Data\User.h"


User::User(const char* userId, const char* name, const char* dateOfBirth)
{
  _userId = userId;
  _name = name;
  _dateOfBirth = dateOfBirth;

}

const char* User::getUserId() const
{
  return _userId.c_str();
}

const char* User::getName() const
{
  return _name.c_str();
}

const char* User::getDateOfBirth() const
{
  return _dateOfBirth.c_str();
}

void User::addAddress(IAddress* address)
{
  _address = address;
}

void User::addAddress(const char* addressLine1, const char* addressLine2, const char* city, const char* state, const char* zip)
{
  _address = new IAddress(addressLine1, addressLine2, city, state, zip);
}

IAddress* User::getAddress() const
{
  return _address;
}

void User::addOrder(IOrder* order)
{
  _order = order;
}

IOrder* User::getOrder(unsigned int orderId) const
{
  return ;
}

const std::vector<IOrder*>& User::getOrders() const
{

}