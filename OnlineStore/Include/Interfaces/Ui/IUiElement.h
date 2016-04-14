#pragma once

#include <functional>

// Describes a basic text-based interface element.
class IUiElement
{
public:
  virtual ~IUiElement() {}

  // Assigns the element callback.
  // The callback is called by processCommand when the user enters a command.
  virtual void setCallback(std::function<bool(const char*)> elementCb) = 0;

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  virtual bool processCommand(const char* c) = 0;
};