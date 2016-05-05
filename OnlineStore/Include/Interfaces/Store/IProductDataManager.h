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
  virtual void addSection(ISection* section) = 0;

  // Returns a list containing the names of each store section.
  virtual const std::vector<const char*> getSectionList() const = 0;

  // Adds a new product to the given section.
  virtual void addProductToSection(const char* sectionName, IProduct* product) = 0;

  // Gets a product given its id.
  virtual const IProduct* getProduct(unsigned int productId) const = 0;

  // Returns the list of products for the given section.
  // Note: Returns an empty vector if section does not exist.
  virtual const std::vector<IProduct*> getProductsForSection(const char* sectionName) const = 0;

  // Adds the given amount of items to the stock of the given product.
  virtual void addItemsToStock(const char* sectionName, unsigned int productId, unsigned int amount) = 0;

  // Removes the given amount of items from the stock of the given product.
  virtual void removeItemsFromStock(const char* sectionName, unsigned int productId, unsigned int amount) = 0;

  // Returns the amount of items in stock for the given product.
  virtual unsigned int getProductStock(const char* sectionName, unsigned int productId) const = 0;

  // Adds the given product to the cart.
  virtual void addProductToCart(IProduct* product, unsigned int quantity) = 0;

  // Removed the given product from the cart.
  virtual void removeProductFromCart(IProduct* product) = 0;

  // Removes all items from the cart.
  virtual void removeAllItemsFromCart() = 0;

  // Returns the list of item currently in cart.
  virtual std::vector<std::pair<IProduct*, unsigned int>> getProductsInCart() const = 0;

  // Returns the total value of all items in the cart.
  virtual float getTotalCartValue() const = 0;
};