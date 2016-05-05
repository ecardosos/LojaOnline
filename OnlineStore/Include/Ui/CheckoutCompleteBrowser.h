#pragma once

#include "Interfaces\Ui\IBrowsingArea.h"

#include <iostream>

class CheckoutCompleteBrowser : public IBrowsingArea
{
  // Output operator; prints page data.
  friend std::ostream& operator<<(std::ostream& os, const CheckoutCompleteBrowser* browsingArea);

public:
  CheckoutCompleteBrowser();

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  bool processCommand(const char* c) override;

  // Forbidden methods.
  CheckoutCompleteBrowser(const CheckoutCompleteBrowser& p) = delete;
  void operator=(const CheckoutCompleteBrowser& p)          = delete;
};