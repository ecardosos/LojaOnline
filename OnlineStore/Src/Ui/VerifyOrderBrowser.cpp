#include "Ui\VerifyOrderBrowser.h"

#include <iostream>

#include "Data\Order.h"

VerifyOrderBrowser::VerifyOrderBrowser()
{
  _order = nullptr;
}

bool VerifyOrderBrowser::processCommand(const char* c)
{
  return false;
}

void VerifyOrderBrowser::setOrderToDisplay(const IOrder* order)
{
  _order = order;
}

std::ostream& operator<<(std::ostream& os, const VerifyOrderBrowser* browsingArea)
{
  if (browsingArea->_order != nullptr)
  {
    os << "Details for order " << browsingArea->_order->getOrderId() << ":" << std::endl << std::endl
       << dynamic_cast<const Order*>(browsingArea->_order);
  }
  else
  {
    os << "There are no orders with the provided Order Id or it is invalid." << std::endl << std::endl
       << "[V] Try again." << std::endl << std::endl
       << "[H] Return to Home.";
  }

    return os;
}