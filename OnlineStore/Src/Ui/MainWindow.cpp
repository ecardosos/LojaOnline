#include "Ui\MainWindow.h"

#include <iostream>
#include <string>
#include <typeinfo>

#include "Store\Manager.h"
#include "Ui\CartBrowser.h"
#include "Ui\CheckoutCompleteBrowser.h"
#include "Ui\CheckoutBrowser.h"
#include "Ui\CheckoutFailBrowser.h"
#include "Ui\ProductBrowser.h"
#include "Ui\ToolbarElement.h"
#include "Ui\VerifyOrderBrowser.h"
#include "Ui\WelcomePage.h"

const std::string MainWindow::s_windowSeparator  = "________________________________________________________________";
const std::string MainWindow::s_sectionSeparator = "================================================================";

MainWindow::MainWindow()
{
  // Home page.
  WelcomePage* welcomePage = new WelcomePage();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::HomePage, welcomePage));

  // Product browser.
  ProductBrowser* productsPage = new ProductBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::ProductPage, productsPage));

  // Cart browser.
  CartBrowser* cartPage = new CartBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::CartPage, cartPage));

  // Checkout browser.
  CheckoutBrowser* checkoutPage = new CheckoutBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::CheckoutPage, checkoutPage));

  // Checkout complete browser.
  CheckoutCompleteBrowser* checkoutCompletePage = new CheckoutCompleteBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::CheckoutCompletePage, checkoutCompletePage));

  // Checkout fail browser.
  CheckoutFailBrowser* checkoutFailPage = new CheckoutFailBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::CheckoutFailPage, checkoutFailPage));

  // Verify order browser.
  VerifyOrderBrowser* verifyOrderPage = new VerifyOrderBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::VerifyOrderPage, verifyOrderPage));

  // Home button.
  IToolbarElement* home = new ToolbarElement("Home", "H");
  std::function<bool(const char*)> homeCb = [this](const char* c)
  {
    this->setCurrentBrowsingArea(PageType::HomePage);
    return true;
  };
  home->setCallback(homeCb);
  _toolbarElements.push_back(home);

  // Cart button.
  IToolbarElement* cart = new ToolbarElement("Cart", "C");
  std::function<bool(const char*)> cartCb = [this](const char* c)
  {
    this->setCurrentBrowsingArea(PageType::CartPage);
    return true;
  };
  cart->setCallback(cartCb);
  _toolbarElements.push_back(cart);

  // Verify orders button
  IToolbarElement* verifyOrder = new ToolbarElement("Verify Orders", "V");
  std::function<bool(const char*)> verifyOrderCb = [this, verifyOrderPage](const char* c)
  {
    std::cout << std::endl
              << "Please enter your Order Id to check details about your order: ";
    std::string orderIdStr;
    std::cin >> orderIdStr;
    unsigned int orderId = std::numeric_limits<unsigned int>::max();
    // Check if provided string is a number.
    try
    {
      orderId = static_cast<unsigned int>(std::stoi(orderIdStr));
    }
    catch (...)
    {
      verifyOrderPage->setOrderToDisplay(nullptr);
    }

    try
    {
      const IOrder* o = Manager::instance().orderManager()->getOrder(static_cast<unsigned int>(orderId));
      verifyOrderPage->setOrderToDisplay(o);
    }
    catch (...)
    {
      verifyOrderPage->setOrderToDisplay(nullptr);
    }
    this->setCurrentBrowsingArea(PageType::VerifyOrderPage);

    return true;
  };
  verifyOrder->setCallback(verifyOrderCb);
  _toolbarElements.push_back(verifyOrder);

  // Section list.
  _sectionList = new ToolbarElement("Select store section", "S");
  std::function<bool(const char*)> listCb = [this, productsPage](const char* c)
  {
    // Gets the list of sections to show the user.
    std::vector<const char*> sections = Manager::instance().productDataManager()->getSectionList();
    std::cout << std::endl << "Store sections:" << std::endl;
    for (unsigned int i = 0; i < sections.size(); i++)
    {
      std::cout << std::endl << "[" << i + 1 << "] " << sections.at(i) << std::endl;
    }
    while (true)
    {
      // Requests selection from user.
      std::cout << std::endl
                << "Please choose your desired section ([B] to abort): ";
      std::string command;
      std::cin >> command;

      if (command == "B")
      {
        return true;
      }

      int selection = -1;
      // std::stoi throws a std::invalid_argument exception if no conversion could be performed.
      // Therefore, simply abort processing of input command if an exception is caught.
      try
      {
        selection = std::stoi(command) - 1;
      }
      catch (...)
      {
        std::cout << std::endl
                  << "Invalid section." << std::endl;
        continue;
      }

      // If command was successfully converted, check if it is within the array bounds.
      if (selection >= 0 && selection < static_cast<int>(sections.size()))
      {
        // Set the current store section to the products page.
        // The page's contents will be updated during the next loop step.
        productsPage->setCurrentSection(sections.at(selection));
      }
      else
      {
        std::cout << std::endl
                  << "Invalid section." << std::endl;
        continue;
      }

      // Finally, sets product browser as the active page.
      this->setCurrentBrowsingArea(PageType::ProductPage);
      break;
    }

    return true;
  };
  _sectionList->setCallback(listCb);

  // Current store page.
  _currentStorePage = PageType::HomePage;
}

MainWindow::~MainWindow()
{
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    delete _toolbarElements.at(i);
  }
  _toolbarElements.clear();

  std::map<PageType, IBrowsingArea*>::iterator it;
  for (it = _storePages.begin(); it != _storePages.end(); it++)
  {
    delete it->second;
  }
  _storePages.clear();

  delete _sectionList;
}

void MainWindow::processCommand(const char* c)
{
  if (c == nullptr)
  {
    return;
  }

  // Toolbar elements.
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    if (_toolbarElements.at(i)->processCommand(c))
    {
      return;
    }
  }

  // List of sections.
  if (_sectionList->processCommand(c))
  {
    return;
  }

  // Browsing area.
  _storePages.at(_currentStorePage)->processCommand(c);
}

void MainWindow::setCurrentBrowsingArea(PageType page)
{
  _currentStorePage = page;
}

void MainWindow::draw()
{
  std::cout << std::endl << std::endl
            << s_windowSeparator
            << std::endl << std::endl;

  // Toolbar buttons.
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    std::cout << dynamic_cast<ToolbarElement*>(_toolbarElements.at(i)) << "\t";
  }

  std::cout << std::endl << std::endl
            << s_sectionSeparator
            << std::endl << std::endl;

  // Section list.
  std::cout << dynamic_cast<ToolbarElement*>(_sectionList);

  std::cout << std::endl << std::endl
            << s_sectionSeparator
            << std::endl << std::endl;

  // Browsing area.
  IBrowsingArea* browsingArea = _storePages.at(_currentStorePage);
  switch (_currentStorePage)
  {
  case PageType::HomePage:
    std::cout << dynamic_cast<WelcomePage*>(browsingArea);
    break;
  case PageType::ProductPage:
    std::cout << dynamic_cast<ProductBrowser*>(browsingArea);
    break;
  case PageType::CartPage:
    std::cout << dynamic_cast<CartBrowser*>(browsingArea);
    break;
  case PageType::CheckoutPage:
    std::cout << dynamic_cast<CheckoutBrowser*>(browsingArea);
    break;
  case PageType::CheckoutCompletePage:
    std::cout << dynamic_cast<CheckoutCompleteBrowser*>(browsingArea);
    break;
  case PageType::CheckoutFailPage:
    std::cout << dynamic_cast<CheckoutFailBrowser*>(browsingArea);
    break;
  case PageType::VerifyOrderPage:
    std::cout << dynamic_cast<VerifyOrderBrowser*>(browsingArea);
    break;
  default:
    // Reset current page to Home.
    _currentStorePage = PageType::HomePage;
    std::cout << dynamic_cast<WelcomePage*>(_storePages.at(PageType::HomePage));
  }

  std::cout << std::endl << std::endl
            << s_windowSeparator
            << std::endl << std::endl;
}