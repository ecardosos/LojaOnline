#pragma once

#include "Interfaces\Ui\IMainWindow.h"

#include <vector>
#include <map>

class IBrowsingArea;
class IToolbarElement;

class MainWindow : public IMainWindow
{
public:
  MainWindow();
  ~MainWindow();

  // Receives a command from the application and forwards it to its interface elements.
  // A command is a simple character input entered by the user while browsing the store.
  void processCommand(const char* c) override;

  // Sets the currently active page in this window.
  void setCurrentBrowsingArea(PageType page) override;

  // Draws the contents of the main window.
  void draw() override;


  // Forbidden methods.
  MainWindow(const MainWindow& m)     = delete;
  void operator=(const MainWindow& m) = delete;

private:

  // Upper window buttons (e.g., Home, Cart).
  std::vector<IToolbarElement*> _toolbarElements;

  // Store section selector.
  IToolbarElement* _sectionList;

  // Main store pages.
  std::map<PageType, IBrowsingArea*> _storePages;

  // The store page being currently viewed.
  PageType _currentStorePage;
};