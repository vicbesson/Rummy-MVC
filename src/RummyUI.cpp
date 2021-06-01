#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include "RummyUI.h"

bool is_number(const std::string& s);
std::string toLower(std::string input);

unsigned int RummyUI::requestCard(std::list<Card*>* hand) {
  return 0;
}

void  RummyUI::playFailed() {
  std::cout << "Invalid meld! Cannot add cards to this meld"
  << std::endl;
}

void  RummyUI::playSucceeded() {
  std::cout << "Cards added to requested meld."
  << std::endl;
}

void RummyUI::showScores(std::vector<Player*> players) {
  for (Player* p : players) {
    if (p->getScore() > 0) {
      std::cout << "The winner is "
      << p->name
      << " with a score of "
      << p->getScore()
      << std::endl;
    }
  }
}

void RummyUI::displayWelcomeMessage() {
  std::cout << "Welcome to Rummy!" << std::endl << std::endl;
}

void RummyUI::displayStartTurn(Player* p) {
  std::cout << p->name
  << "'s turn:"
  << std::endl << std::endl;
}

void RummyUI::displayEndTurn(Player* p) {
  std::cout
  << p->name
  << "'s turn has ended."
  << std::endl << std::endl;
}

void RummyUI::displayPlayerHand(std::list<Card*>* hand) {
  std::cout << "Your hand:" << std::endl;
  for (std::list<Card*>::iterator hit = hand->begin();
      hit != hand->end(); ++hit) {
    if (hit != hand->end()) {
      std::cout << "("
      << Card::getSuit((*hit)->suit)
      << ")"
      << Card::getRank((*hit)->rank)
      << " ";
    } else {
      std::cout << "("
      << Card::getSuit((*hit)->suit)
      << ")"
      << Card::getRank((*hit)->rank);
    }
  }
  std::cout << std::endl << std::endl;
}

void RummyUI::displayMeld(std::list<Card*> meld) {
  std::cout << "Your meld:" << std::endl;
  for (std::list<Card*>::iterator hit = meld.begin();
      hit != meld.end(); ++hit) {
    if (hit != meld.end()) {
      std::cout << "("
      << Card::getSuit((*hit)->suit)
      << ")"
      << Card::getRank((*hit)->rank)
      << " ";
    } else {
      std::cout << "("
      << Card::getSuit((*hit)->suit)
      << ")"
      << Card::getRank((*hit)->rank);
    }
  }
  std::cout << std::endl << std::endl;
}

unsigned int RummyUI::chooseDiscard(std::list<Card*>* hand) {
  std::string command;
  bool valid;
  unsigned int selected;
  std::cout << "Choose a card to discard:"
  << std::endl;
  unsigned int index = 0;
  for (std::list<Card*>::iterator hit = hand->begin();
      hit != hand->end(); ++hit) {
    std::cout << index
    << ". ("
    << Card::getSuit((*hit)->suit)
    << ")"
    << Card::getRank((*hit)->rank)
    << std::endl;
    index++;
  }
  std::cout << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    if (is_number(command)) {
      selected = std::stoi(command);
      if (selected >= hand->size()) {
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
  std::cout << std::endl;
  return selected;
}

unsigned int RummyUI::chooseMeld(std::vector<std::list<Card*>> possibleMelds) {
  std::string command;
  bool valid;
  unsigned int selected;
  std::cout << "Choose a meld:"
  << std::endl;
  unsigned int index = 0;
  for (std::list<Card*> l : possibleMelds) {
    std::cout << index
    << ". ";
    for (std::list<Card*>::iterator hit = l.begin();
        hit != l.end(); ++hit) {
      if (hit != l.end()) {
        std::cout << "("
        << Card::getSuit((*hit)->suit)
        << ")"
        << Card::getRank((*hit)->rank)
        << " ";
      } else {
        std::cout << "("
        << Card::getSuit((*hit)->suit)
        << ")"
        << Card::getRank((*hit)->rank);
      }
    }
    std::cout << std::endl;
    index++;
  }
  std::cout << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    if (is_number(command)) {
      selected = std::stoi(command);
      if (selected >= possibleMelds.size()) {
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
  std::cout << std::endl;
  return selected;
}

bool RummyUI::wantToMeld(std::vector<std::list<Card*>> possibleMelds) {
  std::string command;
  bool valid;
  unsigned int index = 0;
  bool choice = false;
  std::cout << "Possible Melds:"
  << std::endl;
  for (std::list<Card*> l : possibleMelds) {
    std::cout << index
    << ". ";
    for (std::list<Card*>::iterator hit = l.begin();
        hit != l.end(); ++hit) {
      if (hit != l.end()) {
        std::cout << "("
        << Card::getSuit((*hit)->suit)
        << ")"
        << Card::getRank((*hit)->rank)
        << " ";
      } else {
        std::cout << "("
        << Card::getSuit((*hit)->suit)
        << ")"
        << Card::getRank((*hit)->rank);
      }
    }
    std::cout << std::endl;
    index++;
  }
  std::cout << std::endl;
  std::cout << "Do you want to make a meld? (y/n)"
  << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    std::string c = toLower(command);
    if (c == "y" || c == "yes" || c == "n" || c == "no") {
      if (c == "y" || c == "yes") {
        choice = true;
      } else {
        choice = false;
      }
    } else {
      std::cerr << "That is not a valid answer (y/n) "
      << "Please try again." << std::endl;
      valid = false;
    }
  } while (valid == false);
  std::cout << std::endl;
  return choice;
}

bool RummyUI::chooseDraw(Card* c) {
  std::string command;
  bool valid;
  unsigned int selected;
  bool choice = false;
  std::cout << "The top of the discard is "
  << "(" << Card::getSuit(c->suit) << ")"
  << Card::getRank(c->rank)
  << std::endl << std::endl;
  std::cout << "Do you want to draw from the stock or"
  << std::endl
  << "take "
  << "(" << Card::getSuit(c->suit) << ")"
  << Card::getRank(c->rank)
  << " from the top of the discard pile?"
  << std::endl;
  std::cout << "0. draw"
  << std::endl
  << "1. take "
  << "(" << Card::getSuit(c->suit) << ")"
  << Card::getRank(c->rank)
  << std::endl << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    if (is_number(command)) {
      selected = std::stoi(command);
      if (selected == 0) {
        choice = false;
      } else if (selected == 1) {
        choice = true;
      } else {
        std::cerr << "That is not a valid option. "
        << "Please try again." << std::endl;
        valid = false;
      }
    } else {
      std::cerr << "That is not a number. "
      << "Please try again." << std::endl;
      valid = false;
    }
  } while (valid == false);
  std::cout << std::endl;
  return choice;
}

void RummyUI::displayCardAcquired(Player* p, Card* c) {
  std::cout << p->name
  << " has acquired "
  << "(" << Card::getSuit(c->suit) << ")"
  << Card::getRank(c->rank)
  << std::endl << std::endl;
}

bool RummyUI::restock(Card* c) {
  std::string command;
  bool valid;
  std::cout << "The top of the discard is "
  << "(" << Card::getSuit(c->suit) << ")"
  << Card::getRank(c->rank)
  << std::endl
  << "The stock is empty."
  << "Do you want to restock the stock with the discard pile? (y/n)"
  << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    std::string c = toLower(command);
    if (c == "y" || c == "yes" || c == "n" || c == "no") {
      if (c == "y" || c == "yes") {
        return true;
      } else {
        return false;
      }
    } else {
      std::cerr << "That is not a valid answer (y/n) "
      << "Please try again." << std::endl;
      valid = false;
    }
  } while (valid == false);
  std::cout << std::endl;
  return false;
}

unsigned int RummyUI::pickMeld(std::vector<std::list<Card*>> melds) {
  std::string command;
  bool valid;
  unsigned int selected;
  unsigned int index = 0;
  std::cout << "Choose a meld to add card(s) to:"
  << std::endl;
  for (std::list<Card*> l : melds) {
    std::cout << index
    << ". ";
    for (std::list<Card*>::iterator hit = l.begin();
        hit != l.end(); ++hit) {
      if (hit != l.end()) {
        std::cout << "("
        << Card::getSuit((*hit)->suit)
        << ")"
        << Card::getRank((*hit)->rank)
        << " ";
      } else {
        std::cout << "("
        << Card::getSuit((*hit)->suit)
        << ")"
        << Card::getRank((*hit)->rank);
      }
    }
    std::cout << std::endl;
    index++;
  }
  std::cout << "(s)kip"
  << std::endl << std::endl;
  do {
    valid = true;
    command.clear();
    std::cout << ">>";
    getline(std::cin, command);
    if (is_number(command)) {
      selected = std::stoi(command);
      if (selected >= melds.size()) {
        std::cerr << "That is not a valid index. "
        << "Please try again." << std::endl;
        valid = false;
      }
    } else if (toLower(command) == "skip" || toLower(command) == "s") {
      selected = 99;
    } else {
      std::cerr << "That is not a number. "
      << "Please try again." << std::endl;
      valid = false;
    }
  } while (valid == false);
  std::cout << std::endl;
  return selected;
}

void RummyUI::displayCardsAddedToMeld(std::list<Card*> cards) {
  std::cout << "You have layed off ";
  for (std::list<Card*>::iterator hit = cards.begin();
      hit != cards.end(); ++hit) {
    if (hit != cards.end()) {
      std::cout << "("
      << Card::getSuit((*hit)->suit)
      << ")"
      << Card::getRank((*hit)->rank)
      << " ";
    } else {
      std::cout << "("
      << Card::getSuit((*hit)->suit)
      << ")"
      << Card::getRank((*hit)->rank);
    }
  }
  std::cout << std::endl << std::endl;
}

bool is_number(const std::string& s) {
  return !s.empty() && std::find_if(s.begin(),
   s.end(), [](unsigned char c) {
       return !std::isdigit(c);
  }) == s.end();
}

std::string toLower(std::string input) {
    // convert string to lower case
    std::for_each(input.begin(), input.end(), [](char & c) {
        c = ::tolower(c);
    });
    return input;
}
