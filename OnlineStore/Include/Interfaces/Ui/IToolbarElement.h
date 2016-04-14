#pragma once

#include "Interfaces\Ui\IUiElement.h"

// Describes an interface element that acts as an interface button.
class IToolbarElement : public IUiElement
{
public:
  virtual ~IToolbarElement() {}

  // Sets this element's ui display label.
  virtual void setTitle(const char* title) = 0;

  // Returns this element's ui display label.
  virtual const char* getTitle() const = 0;

  // Sets this element's ui command.
  virtual void setCommand(const char* command) = 0;

  // Returns this element's ui command.
  virtual const char* getCommand() const = 0;
};