#include "Ui\CheckoutFailBrowser.h"

#include <iostream>

CheckoutFailBrowser::CheckoutFailBrowser()
{

}

bool CheckoutFailBrowser::processCommand(const char* c)
{
  return false;
}

std::ostream& operator<<(std::ostream& os, const CheckoutFailBrowser* browsingArea)
{
    os << "Sorry, your order could not be placed." << std::endl << std::endl
       << "The transaction has been declined by your bank." << std::endl << std::endl
       << "Please enter another credit card and try again." << std::endl << std::endl
       << "[C] Return to Cart." << std::endl << std::endl
       << "[H] Return to Home.";

    return os;
}