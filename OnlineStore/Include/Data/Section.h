#pragma once

#include "Interfaces\Data\ISection.h"

#include <string>

// Describes a store section, where the user can browse for products.
class Section: public ISection
{
public:
  Section(const char* name);
  ~Section();

  // Sets the section name.
  void setName(const char* name) override;

  // Retuns the section name.
  const char* getName() const override;

  // Adds a single product to a store section.
  void addProduct(IProduct* product) override;

  // Returns the list of products that belong to this section.
  std::vector<IProduct*> getProducts() const override;

  // Returns a product from this section given its id.
  IProduct* getProduct(unsigned int productId) const override;

  // Sets whether products in this section are on sale and the limits of discounts for products in this section.
  // Note: Discounts on individual items are set randomly within the given interval.
  // Note: min and max must be between the interval [0.0, 1.0]; nothing will be done otherwise.
  void setOnSale(bool onSale, float min = 0.0f, float max = 0.0f) override;

  // Returns whether products in this section are on sale.
  bool onSale() const override;

  // Forbidden methods and operators to enforce strict creation of sections with necessary data.
  Section()                         = delete;
  Section(const Section& p)         = delete;
  void operator=(const Section& p)  = delete;

private:
  // Calculates the discount as pseudo-random floating point number within the given range.
  float _calculateDiscount(float min, float max);

  std::string _name;
  std::vector<IProduct*> _products;
  bool _onSale;
};