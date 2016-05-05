#include "Store\Manager.h"

Manager::Manager()
{
  _orderManager = new OrderManager();
  _productDataManager = new ProductDataManager();
  _mainWindow = new MainWindow();
}

Manager::~Manager()
{
  delete _orderManager;
  delete _productDataManager;
  delete _mainWindow;
}

IOrderManager* Manager::orderManager() const
{
  return _orderManager;
}

IProductDataManager* Manager::productDataManager() const
{
  return _productDataManager;
}

IMainWindow* Manager::mainWindow() const
{
  return _mainWindow;
}