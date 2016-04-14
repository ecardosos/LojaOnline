#pragma once

#include <vector>

class IProduct;

// Describes a store section, where the user can browse for products.
class ISection
{
public:
  virtual ~ISection() {}

  // Sets the section name.
  virtual void setName(const char* name) = 0;

  // Retuns the section name.
  virtual const char* getName() const = 0;

  // Adds a single product to a store section.
  virtual void addProduct(IProduct* product) = 0;

  // Returns the list of products that belong to this section.
  virtual std::vector<IProduct*> getProducts() const = 0;

  // Returns a product from this section given its id.
  virtual IProduct* getProduct(unsigned int productId) const = 0;

  // Sets whether products in this section are on sale and apply discounts between min and max.
  // Note: Discounts on individual items are set randomly within the given interval.
  // Note: min and max must be between the interval [0.0, 1.0]; nothing will be done otherwise.
  virtual void setOnSale(bool onSale, float min = 0.0f, float max = 0.0f) = 0;

  // Returns whether products in this section are on sale.
  virtual bool onSale() const = 0;
};