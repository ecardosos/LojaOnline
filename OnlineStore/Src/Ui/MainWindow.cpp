#include "Ui\MainWindow.h"

#include <string>
#include <iostream>
#include <typeinfo>

#include "Store\Manager.h"
#include "Ui\ToolbarElement.h"
#include "Ui\ProductBrowser.h"
#include "Ui\WelcomePage.h"

#define WINDOW_SEPARATOR "//////////////////////////////////////////////////"

#define SECTION_SEPARATOR "=================================================="

MainWindow::MainWindow()
{
  // Home page.
  WelcomePage* welcomePage = new WelcomePage();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::HomePage, welcomePage));

  // Product browser.
  ProductBrowser* productsPage = new ProductBrowser();
  _storePages.insert(std::pair<PageType, IBrowsingArea*>(PageType::ProductPage, productsPage));

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
  IToolbarElement* cart = new ToolbarElement("Cart (not implemented)", "C");
  std::function<bool(const char*)> cartCb = [this](const char* c)
  {
    return true;
  };
  cart->setCallback(cartCb);
  _toolbarElements.push_back(cart);

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
    // Requests selection from user.
    std::cout << std::endl << "Please choose your desired section: ";
    std::string command;
    std::cin >> command;
    int selection = -1;
    try
    {
      selection = std::stoi(command) - 1;
    }
    catch (std::exception e)
    {
      std::cout << "Invalid selection." << std::endl;
      return true;
    }

    if (selection >= 0 && selection < static_cast<int>(sections.size()))
    {
      productsPage->setCurrentSection(sections.at(selection));
    }
    else
    {
      std::cout << "Invalid selection." << std::endl;
    }

    // Sets product browser as the active page.
    this->setCurrentBrowsingArea(PageType::ProductPage);
    return true;
  };
  _sectionList->setCallback(listCb);

  // Current store page.
  _currentStorePage = PageType::HomePage;
}

MainWindow::~MainWindow()
{
  _toolbarElements.clear();
  _storePages.clear();

  delete _sectionList;
}

void MainWindow::processCommand(const char* c)
{
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
            << WINDOW_SEPARATOR
            << std::endl << std::endl;

  // Toolbar buttons.
  for (unsigned int i = 0; i < _toolbarElements.size(); i++)
  {
    std::cout << dynamic_cast<ToolbarElement*>(_toolbarElements.at(i)) << "\t";
  }

  std::cout << std::endl << std::endl
            << SECTION_SEPARATOR
            << std::endl << std::endl;

  // Section list.
  std::cout << dynamic_cast<ToolbarElement*>(_sectionList);

  std::cout << std::endl << std::endl
            << SECTION_SEPARATOR
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
  default:
    // Reset current page to Home.
    _currentStorePage = PageType::HomePage;
    std::cout << dynamic_cast<ProductBrowser*>(_storePages.at(_currentStorePage));
  }

  std::cout << std::endl << std::endl
    << SECTION_SEPARATOR
    << std::endl << std::endl;
}