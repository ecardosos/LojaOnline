#pragma once

#include "Interfaces\Ui\IBrowsingArea.h"

#include <string>

class Address;
class ToolbarElement;

class CheckoutBrowser : public IBrowsingArea
{
  // Output operator; prints page data.
  friend std::ostream& operator<<(std::ostream& os, const CheckoutBrowser* browsingArea);

public:
  CheckoutBrowser();
  ~CheckoutBrowser();

  // Process the given command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  bool processCommand(const char* c) override;

  // Forbidden methods.
  CheckoutBrowser(const CheckoutBrowser& p) = delete;
  void operator=(const CheckoutBrowser& p)  = delete;

private:
  // Auxiliary method that randomly decides whether an order was successful or not
  // to simulate different order outputs.
  bool _processOrder();

  ToolbarElement* _editOrderData;
  ToolbarElement* _completeOrder;

  bool _orderComplete;
  unsigned int _lastOrderId;

  bool _creditCardOk;
  bool _addressOk;

  std::string _cardNumber;
  Address* _shippingAddress;
};