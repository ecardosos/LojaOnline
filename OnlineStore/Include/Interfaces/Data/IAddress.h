#pragma once

// Stores data about an order or user's shipping address.
class IAddress
{
public:
  virtual ~IAddress() {}

  // Sets the first address line.
  virtual void setAddressLine1(const char* line1) = 0;

  // Returns the first address line.
  virtual const char* getAddressLine1() const = 0;

  // Sets the second address line.
  virtual void setAddressLine2(const char* line2) = 0;

  // Returns the second address line.
  virtual const char* getAddressLine2() const = 0;

  // Sets the city name.
  virtual void setCity(const char* city) = 0;

  // Returns the city name.
  virtual const char* getCity() const = 0;

  // Sets the state.
  virtual void setState(const char* state) = 0;

  // Returns the state.
  virtual const char* getState() const = 0;

  // Sets the Zip code.
  virtual void setZip(const char* zip) = 0;

  // Returns the Zip code.
  virtual const char* getZip() const = 0;
};