#pragma once

// Describes a basic text-based interface element.
class IUiElement
{
public:
  virtual ~IUiElement() {}

  // Calls the element callback to process a command.
  // A command is a simple character input entered by the user while browsing the store.
  // Returns true if the given command could be processed, false otherwise.
  virtual bool processCommand(const char* c) = 0;
};