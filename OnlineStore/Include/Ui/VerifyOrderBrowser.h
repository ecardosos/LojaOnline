#pragma once

#include "Interfaces\Ui\IBrowsingArea.h"

#include <iostream>

class IOrder;

class VerifyOrderBrowser : public IBrowsingArea
{
  // Output operator; prints page data.
  friend std::ostream& operator<<(std::ostream& os, const VerifyOrderBrowser* browsingArea);

public:
  VerifyOrderBrowser();

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  bool processCommand(const char* c) override;

  // Sets the order to be displayed.
  void setOrderToDisplay(const IOrder* order);

  // Forbidden methods.
  VerifyOrderBrowser(const VerifyOrderBrowser& p) = delete;
  void operator=(const VerifyOrderBrowser& p) = delete;

private:
  const IOrder* _order;
};