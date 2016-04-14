#include "Ui\ProductBrowser.h"

#include <iostream>
#include <vector>

#include "Data\Product.h"
#include "Store\Manager.h"

ProductBrowser::ProductBrowser()
{

}

void ProductBrowser::setCallback(std::function<bool(const char*)> elementCb)
{
  _elementCb = elementCb;
}

bool ProductBrowser::processCommand(const char* c)
{
  // Do nothing.
  std::cout << "Not implemented." << std::endl;
  return true;
}

void ProductBrowser::draw()
{
  std::cout << this;
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
    os << std::endl << dynamic_cast<Product*>(sectionProducts.at(i));
    os << "[" << i + 1 << "] Add to cart." << std::endl;
  }

  return os;
}