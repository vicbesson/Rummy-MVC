#include <string>
#include <iostream>
#include "Deck.h"
#include "GoFishUI.h"
#include "GoFish.h"
#include "Rummy.h"
#include "RummyUI.h"

int main() {
  Deck* d = new Deck();
  GameUI* ui;
  Game* g;
  d->createStandard();
  std::string command;
  bool valid;
  unsigned int selected;
  std::cout << "Which game would you like to play?"
  << std::endl
  << "0. Go Fish"
  << std::endl
  << "1. Rummy"
  << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    if (command == "0" || command == "1") {
      selected = std::stoi(command);
      if (selected == 0) {
        ui = new GoFishUI();
        g = new GoFish(ui, d);
      } else if (selected = 1) {
        ui = new RummyUI();
        g = new Rummy(ui, d);
      } else {
        std::cerr << "That is not a valid index. "
        << "Please try again." << std::endl;
        valid = false;
      }
    } else {
      std::cerr << "That is not a number. "
      << "Please try again." << std::endl;
      valid = false;
    }
  } while (valid == false);
  g->addPlayer(new Player("John"));
  g->addPlayer(new Player("Danielle"));
  g->addPlayer(new Player("Tara"));
  g->addPlayer(new Player("Erik"));
  g->addPlayer(new Player("Kira"));

  g->start();
  delete g;
}
