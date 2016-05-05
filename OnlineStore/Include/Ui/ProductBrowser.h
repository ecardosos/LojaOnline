#pragma once

#include "Interfaces\Ui\IBrowsingArea.h"

#include <string>

class ProductBrowser : public IBrowsingArea
{
  // Output operator; prints page data.
  friend std::ostream& operator<<(std::ostream& os, const ProductBrowser* browsingArea);

public:
  ProductBrowser();

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  bool processCommand(const char* c) override;

  // Sets the current store section to be displayed by this page.
  void setCurrentSection(const char* section);

  // Returns the current store section.
  const char* getCurrentSection() const;

  // Forbidden methods.
  ProductBrowser(const ProductBrowser& p) = delete;
  void operator=(const ProductBrowser& p) = delete;

private:
  std::string _currentSection;
};