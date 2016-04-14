#pragma once

#include "Store\ProductDataManager.h"

class IUserDataManager;

// Specifies the interface for the one and only instance of a Manager.
class Manager
{
public:
  // Returns the global Manager instance.
  static Manager& instance()
  {
    static Manager instance;
    return instance;
  }

  // Returns the IProductDataManager used to access product related data.
  IProductDataManager* productDataManager() const;

  // Forbidden methods.
  Manager(const Manager& m) = delete;
  void operator=(const Manager& m) = delete;

private:
  Manager();

  //IUserDataManager* _userDataManager;
  IProductDataManager* _productDataManager;
};