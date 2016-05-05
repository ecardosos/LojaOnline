#include "Ui\WelcomePage.h"

#include <iostream>

WelcomePage::WelcomePage()
{

}

bool WelcomePage::processCommand(const char* c)
{
  return false;
}

std::ostream& operator<<(std::ostream& os, const WelcomePage* browsingArea)
{
  return os << std::endl
            << "              Welcome!"
            << std::endl << std::endl
            << "Please choose a store section to begin."
            << std::endl << std::endl;
}