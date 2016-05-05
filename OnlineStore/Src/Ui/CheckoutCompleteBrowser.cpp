#include "Ui\CheckoutCompleteBrowser.h"

#include <iostream>

#include "Store\Manager.h"

CheckoutCompleteBrowser::CheckoutCompleteBrowser()
{

}

bool CheckoutCompleteBrowser::processCommand(const char* c)
{
  return false;
}

std::ostream& operator<<(std::ostream& os, const CheckoutCompleteBrowser* browsingArea)
{
    os << "Thank you! Your order has been placed!" << std::endl << std::endl << std::endl
       << "Order details can be verified on the Verify Orders page." << std::endl << std::endl
       << "Your order Id: " << Manager::instance().orderManager()->getLastOrderId() << std::endl << std::endl
       << "[H] Return to Home.";

    return os;
}