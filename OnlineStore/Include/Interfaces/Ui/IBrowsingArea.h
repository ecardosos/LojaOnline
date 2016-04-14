#pragma once

#include "Interfaces\Ui\IUiElement.h"

// Describes the body of a browsing area.
class IBrowsingArea : public IUiElement
{
public:
  virtual ~IBrowsingArea() {}

  // Draws the page's contents.
  virtual void draw() = 0;
};