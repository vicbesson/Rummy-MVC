#include <list>
#include <vector>
#include "Rummy.h"
#include "RummyUI.h"

Rummy::~Rummy() {
  for (std::list<Card*> l : melds) {
    for (Card* c : l) {
      delete c;
    }
    l.clear();
  }
  melds.clear();
  for (std::vector<std::list<Card*>> v : possibleMelds) {
    for (std::list<Card*> l : v) {
      l.clear();
    }
    v.clear();
  }
  possibleMelds.clear();
  for (Card* c : discard) {
    delete c;
  }
  discard.clear();
}

void Rummy::dealCards(std::vector<Player*> p) {
  unsigned int numCards;
  if (p.size() < 3) {
    numCards = NUM_CARDS_SMALL;
  } else if (p.size() < 5) {
    numCards = NUM_CARDS_MEDIUM;
  } else {
    numCards = NUM_CARDS_LARGE;
  }
  unsigned int neededCards = p.size() * numCards;
  if (deck->size() >= neededCards) {
    for (unsigned int i = 0; i < p.size(); i++) {
      for (unsigned int j = 0; j < numCards; j++) {
        p[i]->addCard(deck->getCard());
      }
    }
  }
  for (Player* player : p) {
    melds.push_back(std::list<Card*>());
    possibleMelds.push_back(std::vector<std::list<Card*>>());
  }
  Card* c = deck->getCard();
  if (c != nullptr) {
    discard.push_back(c);
  }
  static_cast<RummyUI*>(ui)->displayWelcomeMessage();
}

/*
* 1 Begins with displaying the players name and start of turn, displays players hand
* 2 Checks if player has made a meld and if so displays their meld
* 3 If the deck is empty asks the player if they want to restock the deck
* 4 Asks the player if they want to draw from deck or disard and displays the card acquired
* 5 If the player has not made a meld checks the players hand for possible Melds
* and if any exist shows the player the possible melds and asked if they want to make one
* 6 Displays players hand
* 7 Calls function for laying off cards
*/
void Rummy::beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers) {
  static_cast<RummyUI*>(ui)->displayStartTurn(players[playerNum]); //1
  static_cast<RummyUI*>(ui)->displayPlayerHand(players[playerNum]->getHand());
  if (!melds[playerNum].empty()) { //2
    static_cast<RummyUI*>(ui)->displayMeld(melds[playerNum]);
  }
  if (DeckEmpty) { //3
    if (static_cast<RummyUI*>(ui)->restock(discard.front())) {
      unsigned int count = discard.size();
      for (unsigned int i = 0; i < count; i++) {
        Card* c = discard.back();
        deck->addCard(c);
        discard.remove(c);
      }
      if (deck->size() > 0) {
        DeckEmpty = false;
      }
    }
  }
  if (static_cast<RummyUI*>(ui)->chooseDraw(discard.front())) { //4
    players[playerNum]->addCard(discard.front());
    static_cast<RummyUI*>(ui)
    ->displayCardAcquired(players[playerNum], discard.front());
    discard.erase(discard.begin());
  } else {
    if (deck->size() > 0) {
      Card* c = deck->getCard();
      static_cast<RummyUI*>(ui)->displayCardAcquired(players[playerNum], c);
      players[playerNum]->addCard(c);
    } else {
      DeckEmpty = true;
    }
  }
  if (melds[playerNum].empty()) { //5
    if (checkForMelds(players[playerNum]->getHand(), playerNum)) {
      if (static_cast<RummyUI*>(ui)->wantToMeld(possibleMelds[playerNum])) {
        unsigned int choosen =
        static_cast<RummyUI*>(ui)->chooseMeld(possibleMelds[playerNum]);
        melds[playerNum] = possibleMelds[playerNum][choosen];
        for (Card* c : possibleMelds[playerNum][choosen]) {
          players[playerNum]->getHand()->remove(c);
        }
        for (std::list<Card*> l : possibleMelds[playerNum]) {
          l.clear();
        }
        possibleMelds[playerNum].clear();
      }
    }
  }
  //6
  static_cast<RummyUI*>(ui)->displayPlayerHand(players[playerNum]->getHand());
  layingOff(players[playerNum]->getHand(), players); //7
}

void Rummy::afterCardPlayed(Player* currentPlayer, std::vector<Player*> players,
                     Card* played) {
  if (completeMeld(currentPlayer->getHand())) {
    return;
  }
  if (!currentPlayer->getHand()->empty()) {
    unsigned int discardIndex =
    static_cast<RummyUI*>(ui)->chooseDiscard(currentPlayer->getHand());
    Card* c = nullptr;
    unsigned int count = 0;
    for (std::list<Card*>::iterator checking
     = currentPlayer->getHand()->begin();
           checking != currentPlayer->getHand()->end();
           ++checking) {
      if (count == discardIndex) {
        c = *checking;
        currentPlayer->getHand()->remove(*checking);
        break;
      }
      count++;
    }
    if (c != nullptr) {
      discard.push_front(c);
    }
  }
  static_cast<RummyUI*>(ui)->displayEndTurn(currentPlayer);
}

bool Rummy::turnOver() {
  return true;
}

bool Rummy::isOver() const {
  for (Player* p : players) {
    if (p->getHand()->empty()) {
      unsigned int score = 0;
      for (Player* player : players) {
        std::list<Card*> hand = *player->getHand();
        for (Card* c : hand) {
          score += pipValue(c);
        }
      }
      p->addPoints(score);
      return true;
    }
  }
  return false;
}

bool Rummy::checkForMelds(std::list<Card*>* hand, unsigned int playerNum) {
  bool haveMeld = false;
  possibleMelds[playerNum].clear();
  std::list<Card*> toRemove;
  std::vector<Card::Rank> completedRank;
  std::vector<Card*> completedSequence;
  //same rank
  for (std::list<Card*>::iterator checking = hand->begin();
          checking != hand->end();
          ++checking) {
    toRemove.clear();
    unsigned int count = 0;
    for (std::list<Card*>::iterator card = hand->begin();
        card != hand->end(); ++card) {
      if ((*checking)->rank == (*card)->rank
      && !containsRank(completedRank, (*card)->rank)) {
          count++;
          toRemove.push_back(*card);
      }
    }

    if (count >= 3) {
        possibleMelds[playerNum].push_back(toRemove);
        completedRank.push_back(toRemove.front()->rank);
        haveMeld = true;
    }
    //sequence
    toRemove.clear();
    toRemove.push_back(*checking);
    count = 1;
    unsigned int up = 1;
    unsigned int down = 1;
    for (std::list<Card*>::iterator card = hand->begin();
        card != hand->end(); ++card) {
      if ((*card)->suit == (*checking)->suit
       && ((*card)->rank == (*checking)->rank + up
       || (*card)->rank == (*checking)->rank - down)
       && !containsCard(completedSequence, (*card))) {
         if ((*card)->rank == (*checking)->rank + up) {
           up++;
         } else {
            down++;
         }
         count++;
         toRemove.push_back(*card);
       }
    }

    if (count >= 3) {
      possibleMelds[playerNum].push_back(toRemove);
      for (Card* c : toRemove) {
        completedSequence.push_back(c);
      }
      haveMeld = true;
    }
  }
  return haveMeld;
}

Card* Rummy::addToMeld(std::list<Card*>* hand, std::list<Card*> meld) {
  bool typeOfMeld = 1;
  Card::Rank r;
  Card* c = nullptr;
  for (std::list<Card*>::iterator card = meld.begin();
        card != meld.end(); ++card) {
    if (r == (*card)->rank) {
      typeOfMeld = 0;
    }
    r = (*card)->rank;
  }
  for (std::list<Card*>::iterator checking = hand->begin();
          checking != hand->end(); ++checking) {
    for (std::list<Card*>::iterator card = meld.begin();
          card != meld.end(); ++card) {
      if (typeOfMeld == 0) {
        if ((*checking)->rank == (*card)->rank) {
          c = *checking;
          hand->remove(c);
          return c;
        }
      } else {
        if (((*checking)->suit == (*card)->suit)
        && ((*checking)->rank == (*card)->rank + 1
        || (*checking)->rank == (*card)->rank - 1)) {
          c = *checking;
          hand->remove(c);
          return c;
        }
      }
    }
  }
  return c;
}

bool Rummy::completeMeld(std::list<Card*>* hand) {
  std::list<Card*> toRemove;
  //same rank
  for (std::list<Card*>::iterator checking = hand->begin();
          checking != hand->end();
          ++checking) {
    toRemove.clear();
    unsigned int count = 0;
    for (std::list<Card*>::iterator card = hand->begin();
        card != hand->end(); ++card) {
      if ((*checking)->rank == (*card)->rank) {
          count++;
          toRemove.push_back(*card);
      }
    }
    if (count == hand->size()) {
        static_cast<RummyUI*>(ui)->displayCardsAddedToMeld(toRemove);
        for (Card* c : toRemove) {
          discard.push_front(c);
          hand->remove(c);
        }
        return true;
    }
    //sequence
    toRemove.clear();
    toRemove.push_back(*checking);
    count = 1;
    unsigned int up = 1;
    unsigned int down = 1;
    for (std::list<Card*>::iterator card = hand->begin();
        card != hand->end(); ++card) {
      if ((*card)->suit == (*checking)->suit
       && ((*card)->rank == (*checking)->rank + up
       || (*card)->rank == (*checking)->rank - down)) {
         if ((*card)->rank == (*checking)->rank + up) {
           up++;
         } else {
            down++;
         }
         count++;
         toRemove.push_back(*card);
       }
    }
    if (count == hand->size()) {
      static_cast<RummyUI*>(ui)->displayCardsAddedToMeld(toRemove);
      for (Card* c : toRemove) {
        discard.push_front(c);
        hand->remove(c);
      }
      return true;
    }
  }
  return false;
}
/*
* Player picks a current meld and the code checks if the players hand
* is able to lay off to that meld. If not repeats function until a valid meld
* is choosen or until the player chooses to skip.
*/
void Rummy::layingOff(std::list<Card*>* hand, std::vector<Player*> players) {
  unsigned int index =
  static_cast<RummyUI*>(ui)->pickMeld(melds);
  if (index != 99) {
    if (!melds[index].empty()) {
      Card* c = nullptr;
      std::list<Card*> cardstoAdd;
      do {
        c = addToMeld(hand, melds[index]);
        if (c != nullptr) {
          cardstoAdd.push_back(c);
        }
      } while (c != nullptr);
      if (!cardstoAdd.empty()) {
        ui->playSucceeded();
        for (Card* card : cardstoAdd) {
          melds[index].push_back(card);
        }
        static_cast<RummyUI*>(ui)->displayCardsAddedToMeld(cardstoAdd);
        cardstoAdd.clear();
      } else {
        ui->playFailed();
        layingOff(hand, players);
      }
    } else {
      ui->playFailed();
      layingOff(hand, players);
    }
  }
}

unsigned int Rummy::pipValue(Card* c) const {
  switch (c->rank) {
    case Card::ACE:
      return 1;
    case Card::TWO:
      return 2;
    case Card::THREE:
      return 3;
    case Card::FOUR:
      return 4;
    case Card::FIVE:
      return 5;
    case Card::SIX:
      return 6;
    case Card::SEVEN:
      return 7;
    case Card::EIGHT:
      return 8;
    case Card::NINE:
      return 9;
    case Card::TEN:
      return 10;
    case Card::JACK:
      return 10;
    case Card::QUEEN:
      return 10;
    case Card::KING:
      return 10;
  }
  return 0;
}

bool Rummy::containsRank(const std::vector<Card::Rank>& list, Card::Rank x) {
  for (Card::Rank r : list) {
    if (r == x) {
      return true;
    }
  }
  return false;
}

bool Rummy::containsCard(const std::vector<Card*>& list, Card* x) {
  for (Card* c : list) {
    if (c == x) {
      return true;
    }
  }
  return false;
}
