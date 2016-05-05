#include "Data\Address.h"

#include <cassert>

Address::Address()
{
  _addressLine1 = "";
  _addressLine2 = "";
  _city = "";
  _state = "";
  _zip = "";
}

Address::Address(const char* addressLine1, const char* addressLine2, const char* city, const char* state, const char* zip)
{
  assert(addressLine1);
  assert(addressLine2);
  assert(city);
  assert(state);
  assert(zip);

  _addressLine1 = addressLine1;
  _addressLine2 = addressLine2;
  _city = city;
  _state = state;
  _zip = zip;
}

Address::Address(const Address& a)
{
  _addressLine1 = a._addressLine1;
  _addressLine2 = a._addressLine2;
  _city         = a._city;
  _state        = a._state;
  _zip          = a._zip;
}

void Address::setAddressLine1(const char* line1)
{
  assert(line1);

  _addressLine1 = line1;
}

const char* Address::getAddressLine1() const
{
  return _addressLine1.c_str();
}

void Address::setAddressLine2(const char* line2)
{
  assert(line2);

  _addressLine2 = line2;
}

const char* Address::getAddressLine2() const
{
  return _addressLine2.c_str();
}

void Address::setCity(const char* city)
{
  assert(city);

  _city = city;
}

const char* Address::getCity() const
{
  return _city.c_str();
}

void Address::setState(const char* state)
{
  assert(state);

  _state = state;
}

const char* Address::getState() const
{
  return _state.c_str();
}

void Address::setZip(const char* zip)
{
  assert(zip);

  _zip = zip;
}

const char* Address::getZip() const
{
  return _zip.c_str();
}

std::ostream& operator<<(std::ostream& os, const Address* address)
{
  os << "Address Line 1: " << address->getAddressLine1() << std::endl
     << "Address Line 2: " << address->getAddressLine2() << std::endl
     << "City:           " << address->getCity() << std::endl
     << "State/Province: " << address->getState() << std::endl
     << "ZIP Code:       " << address->getZip();

  return os;
}