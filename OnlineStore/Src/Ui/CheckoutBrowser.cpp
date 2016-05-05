#include "Ui\CheckoutBrowser.h"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#include "Data\Address.h"
#include "Data\Order.h"
#include "Store\Manager.h"
#include "Ui\ToolbarElement.h"

CheckoutBrowser::CheckoutBrowser()
{
  _cardNumber = "";
  _shippingAddress = new Address();

  _creditCardOk = false;
  _addressOk = false;

  _editOrderData = new ToolbarElement("Edit credit card and address", "E");
  std::function<bool(const char*)> orderDataCb = [this](const char*)
  {
    bool dataOk = false;
    // Get credit card number.
    _creditCardOk = false;
    _cardNumber = "";
    while (!dataOk)
    {
      dataOk = true;
      std::cout << std::endl
                << "Please enter your credit card number ([B] to abort): ";
      std::string cardNumber;
      std::cin >> cardNumber;
      if (strcmp(cardNumber.c_str(), "B") == 0)
      {
        return true;
      }
      // Check if string lenght is valid.
      if (cardNumber.length() != 16)
      {
        dataOk = false;
        std::cout << std::endl
                  << "Invalid card number." << std::endl;
      }
      // Check if provided string is a number
      if (!std::all_of(cardNumber.begin(), cardNumber.end(), ::isdigit))
      {
        dataOk = false;
        std::cout << std::endl
                  << "Invalid card number." << std::endl;
      }

      if (dataOk)
      {
        _creditCardOk = true;
        _cardNumber = cardNumber;
      }
    }

    dataOk = false;
    // Get address data.
    _addressOk = false;
    delete _shippingAddress;
    std::string addressLine1, addressLine2, city, state, zipCode;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl
              << "Please enter your address line 1: ";
    std::getline(std::cin, addressLine1);

    std::cout << std::endl
              << "Please enter your address line 2: ";
    std::getline(std::cin, addressLine2);

    std::cout << std::endl
              << "Please enter your city: ";
    std::getline(std::cin, city);

    std::cout << std::endl
              << "Please enter your state/province: ";
    std::getline(std::cin, state);

    std::cout << std::endl
              << "Please enter your ZIP Code: ";
    std::getline(std::cin, zipCode);

    _addressOk = true;
    _shippingAddress = new Address(addressLine1.c_str(),
                                   addressLine2.c_str(),
                                   city.c_str(),
                                   state.c_str(),
                                   zipCode.c_str());

    return true;
  };
  _editOrderData->setCallback(orderDataCb);

  _completeOrder = new ToolbarElement("Complete order", "O");
  std::function<bool(const char*)> completeCb = [this](const char*)
  {
    if (_creditCardOk && _addressOk && _processOrder())
    {
      // Order date.
      std::time_t t = std::time(0);
      char d[30];
      ctime_s(d, sizeof(d), &t);
      std::string date = d;

      float orderValue = Manager::instance().productDataManager()->getTotalCartValue();
      IOrder* order = new Order(date.c_str(), new Address(*_shippingAddress), orderValue);

      // Add products to order.
      std::vector<std::pair<IProduct*, unsigned int>> orderProducts = Manager::instance().productDataManager()->getProductsInCart();
      for (unsigned int i = 0; i < orderProducts.size(); i++)
      {
        // TODO: Update stock amounts after this order.
        IProduct* p = orderProducts.at(i).first;
        order->addItem(p);
      }

      // Add it to the order manager.
      Manager::instance().orderManager()->addOrder(order);

      // Clear cart.
      Manager::instance().productDataManager()->removeAllItemsFromCart();

      // Update the browsing area with the checkout complete page.
      Manager::instance().mainWindow()->setCurrentBrowsingArea(PageType::CheckoutCompletePage);
    }
    else
    {
      // Update the browsing area with the checkout failed page.
      Manager::instance().mainWindow()->setCurrentBrowsingArea(PageType::CheckoutFailPage);
    }

    _cardNumber = "";
    _shippingAddress->setAddressLine1("");
    _shippingAddress->setAddressLine2("");
    _shippingAddress->setCity("");
    _shippingAddress->setState("");
    _shippingAddress->setZip("");
    _creditCardOk = false;
    _addressOk = false;

    return true;
  };
  _completeOrder->setCallback(completeCb);
}

CheckoutBrowser::~CheckoutBrowser()
{
  delete _editOrderData;
  delete _completeOrder;
  delete _shippingAddress;
}

bool CheckoutBrowser::processCommand(const char* c)
{
  if (c == nullptr)
  {
    return false;
  }

  // If an order has been completed, return to Home.
  if (_orderComplete)
  {
    // Reset last order information.
    _orderComplete = false;
    _lastOrderId = std::numeric_limits<unsigned int>::max();

    Manager::instance().mainWindow()->setCurrentBrowsingArea(PageType::HomePage);
    return true;
  }

  // Otherwise, process commands normally.
  if (std::strcmp(_editOrderData->getCommand(), c) == 0)
  {
    return _editOrderData->processCommand(c);
  }

  if (std::strcmp(_completeOrder->getCommand(), c) == 0)
  {
    return _completeOrder->processCommand(c);
  }

  return false;
}

bool CheckoutBrowser::_processOrder()
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, 100);

  int checkoutProb = distr(eng);

  // 75% chances of success.
  return (checkoutProb <= 75) ? true : false;
}

std::ostream& operator<<(std::ostream& os, const CheckoutBrowser* browsingArea)
{
  os << "Payment information:" << std::endl << std::endl
     << "Credit card number: " << browsingArea->_cardNumber << std::endl << std::endl
     << "Address information:" << std::endl << std::endl
     << browsingArea->_shippingAddress << std::endl << std::endl
     << browsingArea->_editOrderData << std::endl << std::endl;

  if (browsingArea->_creditCardOk && browsingArea->_addressOk)
  {
    os << browsingArea->_completeOrder;
  }
  else
  {
    os << "Please enter your credit card and address information to proceed.";
  }

  return os;
}