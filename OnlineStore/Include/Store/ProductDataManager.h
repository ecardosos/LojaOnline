#pragma once

#include "Interfaces\Store\IProductDataManager.h"

class ProductDataManager : public IProductDataManager
{
public:
  ProductDataManager();
  ~ProductDataManager();

  // Adds a new product section.
  void addSection(ISection* section) override;

  // Returns a list containing the names of each store section.
  const std::vector<const char*> getSectionList() const override;

  // Adds a new product to the given section.
  void addProductToSection(const char* sectionName, IProduct* product) override;

  // Gets a product given its id.
  const IProduct* getProduct(unsigned int productId) const override;

  // Returns the list of products for the given section.
  const std::vector<IProduct*> getProductsForSection(const char* sectionName) const override;

  // Adds the given amount of items to the stock of the given product.
  void addItemsToStock(const char* sectionName, unsigned int productId, unsigned int amount) override;

  // Removes the given amount of items from the stock of the given product.
  void removeItemsFromStock(const char* sectionName, unsigned int productId, unsigned int amount) override;

  // Returns the amount of items in stock for the given product.
  unsigned int getProductStock(const char* sectionName, unsigned int productId) const override;

  // Adds the given item to the cart.
  void addProductToCart(IProduct* product, unsigned int quantity) override;

  // Removes the given product from the cart.
  void removeProductFromCart(IProduct* product) override;

  // Removes all items from the cart.
  void removeAllItemsFromCart() override;

  // Returns the list of item currently in cart.
  std::vector<std::pair<IProduct*, unsigned int>> getProductsInCart() const override;

  // Returns the total value of all items in the cart.
  float getTotalCartValue() const override;

  // Forbidden methods.
  ProductDataManager(const ProductDataManager& m) = delete;
  void operator=(const ProductDataManager& m)     = delete;

private:
  // Retuns the section with the given name or null if it doesn't exist.
  ISection* _getSectionByName(const char* sectionName) const;

  // Associates an IProduct with its number of items in cart.
  // Vector indices are used to process commands for individual items.
  std::vector<std::pair<IProduct*, unsigned int>> _cart;

  std::vector<ISection*> _productSections;
};