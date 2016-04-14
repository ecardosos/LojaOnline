#include "Ui\WelcomePage.h"

#include <iostream>

WelcomePage::WelcomePage()
{

}

void WelcomePage::setCallback(std::function<bool(const char*)> elementCb)
{
  // Do nothing.
}

bool WelcomePage::processCommand(const char* c)
{
  // Do nothing.
  return true;
}

void WelcomePage::draw()
{
  std::cout << this;
}

std::ostream& operator<<(std::ostream& os, const WelcomePage* browsingArea)
{
  return os << std::endl
            << "              Welcome!"
            << std::endl << std::endl
            << "Please choose a store section to begin."
            << std::endl << std::endl;
}