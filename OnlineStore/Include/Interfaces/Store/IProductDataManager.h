#pragma once

#include <vector>

class IProduct;
class ISection;

// Manages all operations regarding products and sections.
class IProductDataManager
{
public:
  virtual ~IProductDataManager() {}

  // Adds a new product section.
  virtual void addSection(ISection* newSection) = 0;

  // Returns a list containing the names of each store section.
  virtual const std::vector<const char*> getSectionList() const = 0;

  // Adds a new product to the given section.
  virtual void addItemToSection(const char* sectionName, IProduct* newProduct) = 0;

  // Returns the list of products for the given section.
  // Note: Returns an empty vector if section does not exist.
  virtual const std::vector<IProduct*> getProductsForSection(const char* sectionName) const = 0;

  // Adds the given amount of items to the stock of the given product.
  virtual void addItemToStock(const char* sectionName, unsigned int productId, unsigned int amount) = 0;

  // Removes the given amount of items from the stock of the given product.
  // Note: Assumes the given amount is NOT greater than the current item stock.
  virtual void removeItemFromStock(const char* sectionName, unsigned int productId, unsigned int amount) = 0;

  // Returns the amount of items in stock for the given product.
  // Note: Returns -1 if either section or product are invalid.
  virtual int getProductStock(const char* sectionName, unsigned int productId) const = 0;
};