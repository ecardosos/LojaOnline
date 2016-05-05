#include "Ui\CartBrowser.h"

#include <conio.h>
#include <iostream>

#include "Data\Product.h"
#include "Store\Manager.h"
#include "Ui\ToolbarElement.h"

CartBrowser::CartBrowser()
{
  // Checkout
  _checkout = new ToolbarElement("Checkout", "T");
  std::function<bool(const char*)> checkoutCb = [](const char* c)
  {
    if (Manager::instance().productDataManager()->getProductsInCart().size() > 0)
    {
      Manager::instance().mainWindow()->setCurrentBrowsingArea(PageType::CheckoutPage);
    }

    return true;
  };
  _checkout->setCallback(checkoutCb);
}
CartBrowser::~CartBrowser()
{
  delete _checkout;
}

bool CartBrowser::processCommand(const char* c)
{
  if (c == nullptr)
  {
    return false;
  }

  // Checkout button
  if (std::strcmp(_checkout->getCommand(), c) == 0)
  {
    return _checkout->processCommand(c);
  }

  // Item selections.
  int selection = -1;
  // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
  // Therefore, simply abort processing of input command if an exception is caught.
  try
  {
    selection = std::stoi(c) - 1;
  }
  catch (...)
  {
    std::cout << std::endl
              << "Invalid selection." << std::endl << std::endl
              << "Press any key to continue...";
    _getch();

    return true;
  }

  std::vector<std::pair<IProduct*, unsigned int>> productsInCart =
    Manager::instance().productDataManager()->getProductsInCart();

  // If command was successfully converted, check if it is within the array bounds.
  if (selection >= 0 && selection < static_cast<int>(productsInCart.size()))
  {
    std::pair<IProduct*, unsigned int> p = productsInCart.at(selection);
    Manager::instance().productDataManager()->removeProductFromCart(p.first);

    std::cout << std::endl
      << "You removed 1 "<< p.first->getName() << " (" << p.first->getManufacturer() << ") from your cart." << std::endl << std::endl
      << "Press any key to continue...";
    _getch();
  }
  else
  {
    std::cout << std::endl
              << "Invalid selection." << std::endl << std::endl
              << "Press any key to continue...";
    _getch();
  }

  return true;
}

std::ostream& operator<<(std::ostream& os, const CartBrowser* browsingArea)
{
  os << "Products in cart:" << std::endl << std::endl;

  std::vector<std::pair<IProduct*, unsigned int>> productsInCart =
    Manager::instance().productDataManager()->getProductsInCart();

  if (productsInCart.empty())
  {
    os << "There are no items in your cart right now." << std::endl << std::endl;
  }
  else
  {
    for (unsigned int i = 0; i < productsInCart.size(); i++)
    {
      std::pair<IProduct*, unsigned int> p = productsInCart.at(i);
      os << p.first->getName() << std::endl
        << "Quantity: " << p.second << std::endl
        << "Price: US$ " << p.first->getDiscountedPrice() * p.second << std::endl
        << "[" << i + 1 << "] Remove from cart." << std::endl << std::endl;
    }
  }

  os << "Order total: US$ " << Manager::instance().productDataManager()->getTotalCartValue() << std::endl
     << std::endl << browsingArea->_checkout;

  return os;
}