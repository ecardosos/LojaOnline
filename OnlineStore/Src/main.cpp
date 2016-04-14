#include <iostream>
#include <string>
#include <vector>

#include "Core\Application.h"
#include "Data\Product.h"
#include "Data\Section.h"
#include "Store\Manager.h"
#include "Store\ProductDataManager.h"
#include "Ui\ToolbarElement.h"

int main()
{
  // Test sections.
  Section* s1 = new Section("Entertainment");
  s1->addProduct(new Product("BREAK", "Mamoru Miyano's first album.", "KING RECORDS", 20, 10));
  s1->addProduct(new Product("WONDER", "Mamoru Miyano's second album.", "KING RECORDS", 20, 15));
  s1->addProduct(new Product("FANTASISTA", "Mamoru Miyano's third album.", "KING RECORDS", 20, 20));
  s1->addProduct(new Product("DABA PROJECT: HORSE LIFE GAME", "DABA's third DVD.", "DABA", 50, 30));

  Section* s2 = new Section("Books&Comics");
  s2->addProduct(new Product("Journey", "Mamoru Miyano's artist book.", "Miyano, Mamoru", 30, 100));
  s2->addProduct(new Product("Hiradzume", "Daisuke Hirakawa's autobiography.", "Hirakawa, Daisuke", 60, 15));
  s2->addProduct(new Product("Hakoniwa no Reijou Tantei (1)", "The story of Akira Satou and the supernatural detective agency Hakoniwa.", "Tachibana, Shinnosuke", 5, 90));
  s2->setOnSale(true, 0.1f, 0.3f);
  
  Section* s4 = new Section("Consoles");
  s4->addProduct(new Product("New NINTENDO 3DS XL", "", "NINTENDO", 160, 150));
  s4->addProduct(new Product("NINTENDO WiiU", "", "NINTENDO", 360, 300));
  s4->addProduct(new Product("Xbox ONE 500GB", "", "Microsoft", 375, 1000));
  s4->addProduct(new Product("PlayStation 4", "", "SONY", 345, 100));
  s4->addProduct(new Product("SONY PSVita", "", "SONY", 180, 500));

  Section* s5 = new Section("Games");
  s5->addProduct(new Product("", "", "", 30, 100));


  // Access to Manager instance to obtain the ProductDataManager instance.
  IProductDataManager* mgr = Manager::instance().productDataManager();
  mgr->addSection(s1);
  mgr->addSection(s2);

  Application* app = new Application();
  app->run();

  return 0;
}