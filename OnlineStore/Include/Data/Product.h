#pragma once

#include "Interfaces\Data\IProduct.h"

#include <string>

class Product : public IProduct
{
  // Output operator; prints this product's data.
  friend std::ostream& operator<<(std::ostream& os, const Product& product);
  friend std::ostream& operator<<(std::ostream& os, const Product* product);

public:
  Product(const char* name, const char* description, const char* manufacturer, float initialPrice, unsigned int initialStock);

  // Sets the product's name.
  void setName(const char* name) override;

  // Returns the product's name.
  const char* getName() const override;

  // Returns the product's store id.
  unsigned int getProductId() override;

  // Sets the product's description.
  void setDescription(const char* description) override;

  // Returns the product's description.
  const char* getDescription() const override;

  // Sets the product's manufacturer.
  void setManufacturer(const char* manufacturer) override;

  // Returns the product's manufacturer.
  const char* getManufacturer() const override;

  // Sets the product's price.
  void setPrice(float price) override;

  // Returns the product's price.
  float getPrice() const override;

  // Enables or disables a sale for this product.
  void setOnSale(bool onSale) override;

  // Returns whether this product is on sale.
  bool onSale() const override;

  // Sets the sale percentage.
  // Note: The value must be between the interval [0.0, 1.0].
  void setDiscount(float discount) override;

  // Gets the sale percentage for this item.
  // Note: Value returned is between the interval [0.0, 1.0].
  float getDiscount() const override;

  // Adds the given amount of items to this product's stock.
  void addItemsToStock(unsigned int amount) override;

  // Removes the given amount of items from this product's stock.
  void removeItemsFromStock(unsigned int amount) override;

  // Returns the amount of items in stock this product.
  unsigned int getItemStock() const override;

  // Forbidden methods and operators to enforce strict creation of products with necessary data.
  Product()                        = delete;
  Product(const Product& p)        = delete;
  void operator=(const Product& p) = delete;

private:
  static unsigned int s_globalId;
  unsigned int _productId;

  std::string _name;
  std::string _description;
  std::string _manufacturer;

  float _price;
  float _discount;

  bool _onSale;

  unsigned int _itemStock;
};