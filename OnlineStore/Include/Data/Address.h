#pragma once

#include "Interfaces\Data\IAddress.h"

#include <string>

// Stores data about an order or user's shipping address.
class Address : public IAddress
{
  // Output operator; prints this Address' data.
  friend std::ostream& operator<<(std::ostream& os, const Address* address);

public:
  Address();
  Address(const char* addressLine1, const char* addressLine2, const char* city, const char* state, const char* zip);
  Address(const Address& a);

  // Sets the first address line.
  virtual void setAddressLine1(const char* line1) override;

  // Returns the first address line.
  virtual const char* getAddressLine1() const override;

  // Sets the second address line.
  virtual void setAddressLine2(const char* line2) override;

  // Returns the second address line.
  virtual const char* getAddressLine2() const override;

  // Sets the city name.
  virtual void setCity(const char* city) override;

  // Returns the city name.
  virtual const char* getCity() const override;

  // Sets the state.
  virtual void setState(const char* state) override;

  // Returns the state.
  virtual const char* getState() const override;

  // Sets the Zip code.
  virtual void setZip(const char* zip) override;

  // Returns the Zip code.
  virtual const char* getZip() const override;

  // Forbidden methods.
  void operator=(const Address& a) = delete;

private:
  std::string _addressLine1;
  std::string _addressLine2;

  std::string _city;
  std::string _state;
  std::string _zip;
};