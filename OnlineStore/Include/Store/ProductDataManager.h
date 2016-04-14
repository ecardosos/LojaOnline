#pragma once

#include "Interfaces\Store\IProductDataManager.h"

class IProduct;
class ISection;

class ProductDataManager : public IProductDataManager
{
public:
  ProductDataManager();
  ~ProductDataManager();

  // Adds a new product section.
  void addSection(ISection* newSection) override;

  // Returns a list containing the names of each store section.
  const std::vector<const char*> getSectionList() const override;

  // Adds a new product to the given section.
  void addItemToSection(const char* sectionName, IProduct* newProduct) override;

  // Returns the list of products for the given section.
  const std::vector<IProduct*> getProductsForSection(const char* sectionName) const override;

  // Adds the given amount of items to the stock of the given product.
  void addItemToStock(const char* sectionName, unsigned int productId, unsigned int amount) override;

  // Removes the given amount of items from the stock of the given product.
  // Note: Assumes the given amount is NOT greater than the current item stock.
  void removeItemFromStock(const char* sectionName, unsigned int productId, unsigned int amount) override;

  // Returns the amount of items in stock for the given product.
  // Note: Returns -1 if either section or product are invalid.
  int getProductStock(const char* sectionName, unsigned int productId) const override;

  // Forbidden methods.
  ProductDataManager(const ProductDataManager& m) = delete;
  void operator=(const ProductDataManager& m)     = delete;

private:
  // Retuns the section with the given name or null if it doesn't exist.
  ISection* _getSectionByName(const char* sectionName) const;

  std::vector<ISection*> _productSections;
};