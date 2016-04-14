#include "Store\Manager.h"

#include "Store\ProductDataManager.h"

Manager::Manager()
{
  _productDataManager = new ProductDataManager();
}

IProductDataManager* Manager::productDataManager() const
{
  return _productDataManager;
}