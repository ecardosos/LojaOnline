#include "Ui\ProductBrowser.h"

#include <conio.h>
#include <iostream>
#include <vector>

#include "Data\Product.h"
#include "Store\Manager.h"

ProductBrowser::ProductBrowser()
{

}

bool ProductBrowser::processCommand(const char* c)
{
  if (c == nullptr)
  {
    return false;
  }

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

  std::vector<IProduct*> sectionProducts =
    Manager::instance().productDataManager()->getProductsForSection(_currentSection.c_str());

  // If command was successfully converted, check if it is within the array bounds.
  if (selection >= 0 && selection < static_cast<int>(sectionProducts.size()))
  {
    for (unsigned int i = 0; i < sectionProducts.size(); i++)
    {
      if (selection == i)
      {
        IProduct* p = sectionProducts.at(i);
        Manager::instance().productDataManager()->addProductToCart(p, 1u);

        std::cout << std::endl
                  << "You added " << p->getName() << " (" << p->getManufacturer() << ") to your cart." << std::endl << std::endl
                  << "Press any key to continue...";
        _getch();
      }
    }
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

void ProductBrowser::setCurrentSection(const char* section)
{
  _currentSection = section;
}

const char* ProductBrowser::getCurrentSection() const
{
  return _currentSection.c_str();
}

std::ostream& operator<<(std::ostream& os, const ProductBrowser* browsingArea)
{
  std::string section = browsingArea->getCurrentSection();
  std::vector<IProduct*> sectionProducts = Manager::instance().productDataManager()->getProductsForSection(section.c_str());

  os << "List of products in section " << section << ":"
     << std::endl << std::endl;

  for (unsigned int i = 0; i < sectionProducts.size(); i++)
  {
    IProduct* p = sectionProducts.at(i);
    os << std::endl << dynamic_cast<Product*>(p) << std::endl
       << "Items in stock: " << p->getItemStock() << std::endl;

    // Removes the "add to cart" command label if there are no items in stock.
    if (p->getItemStock() > 0)
    {
      os << "[" << i + 1 << "] Add to cart." << std::endl;
    }
    else
    {
      os << "Item currently unavailable." << std::endl;
    }
  }

  return os;
}