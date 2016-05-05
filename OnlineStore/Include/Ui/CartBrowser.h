#pragma once

#include "Interfaces\Ui\IBrowsingArea.h"

#include <utility>
#include <vector>

class ToolbarElement;

class CartBrowser : public IBrowsingArea
{
  // Output operator; prints page data.
  friend std::ostream& operator<<(std::ostream& os, const CartBrowser* browsingArea);

public:
  CartBrowser();
  ~CartBrowser();

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  bool processCommand(const char* c) override;

  // Forbidden methods.
  CartBrowser(const CartBrowser& p) = delete;
  void operator=(const CartBrowser& p) = delete;

private:
  ToolbarElement* _checkout;
};