#pragma once

enum PageType
{
  HomePage,
  ProductPage,
  CartPage,
  CheckoutPage,
  CheckoutCompletePage,
  CheckoutFailPage,
  OrdersPage,
  VerifyOrderPage
};

// Responsible for storing and managing the store's interface elements.
class IMainWindow
{
public:
  virtual ~IMainWindow() {}

  // Receives a command from the application and forwards it to its interface elements.
  // A command is a simple character input entered by the user while browsing the store.
  virtual void processCommand(const char* c) = 0;

  // Sets the currently active page in this window.
  virtual void setCurrentBrowsingArea(PageType page) = 0;

  // Draws the contents of the main window.
  virtual void draw() = 0;
};