#pragma once

// Describes a product to be sold in the store.
class IProduct
{
public:
  virtual ~IProduct() {}

  // Sets the product's name.
  virtual void setName(const char* name) = 0;

  // Returns the product's name.
  virtual const char* getName() const = 0;

  // Returns the product's store id.
  virtual unsigned int getProductId() = 0;

  // Sets the product's description.
  virtual void setDescription(const char* description) = 0;

  // Returns the product's description.
  virtual const char* getDescription() const = 0;

  // Sets the product's manufacturer.
  virtual void setManufacturer(const char* manufacturer) = 0;

  // Returns the product's manufacturer.
  virtual const char* getManufacturer() const = 0;

  // Sets the product's price.
  virtual void setPrice(float price) = 0;

  // Returns the product's price.
  virtual float getPrice() const = 0;

  // Enables or disables a sale for this product.
  virtual void setOnSale(bool onSale) = 0;

  // Returns whether this product is on sale.
  virtual bool onSale() const = 0;

  // Sets the sale percentage.
  // Note: The value must be between the interval [0.0, 1.0].
  virtual void setDiscount(float discount) = 0;

  // Gets the sale percentage for this item.
  // Note: Value returned is between the interval [0.0, 1.0].
  virtual float getDiscount() const = 0;

  // Adds the given amount of items to this product's stock.
  virtual void addItemsToStock(unsigned int amount) = 0;

  // Removes the given amount of items from this product's stock.
  // Note: Assumes the given amount is NOT greater than the current item stock.
  virtual void removeItemsFromStock(unsigned int amount) = 0;

  // Returns the amount of items in stock this product.
  virtual unsigned int getItemStock() const = 0;
};