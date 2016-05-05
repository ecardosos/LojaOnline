#pragma once

#include "Store\OrderManager.h"
#include "Store\ProductDataManager.h"
#include "Ui\MainWindow.h"

// Specifies the access to the one and only Manager instance.
class Manager
{
public:
  ~Manager();

  // Returns the global Manager instance.
  static Manager& instance()
  {
    static Manager instance;
    return instance;
  }

  // Returns the IOrderManager, used to retrieve order data.
  IOrderManager* orderManager() const;

  // Returns the IProductDataManager, used to access product related data.
  IProductDataManager* productDataManager() const;

  // Returns the IMainWindow instance.
  IMainWindow* mainWindow() const;

  // Forbidden methods.
  Manager(const Manager& m) = delete;
  void operator=(const Manager& m) = delete;

private:
  Manager();

  IOrderManager* _orderManager;
  IProductDataManager* _productDataManager;
  IMainWindow* _mainWindow;
};