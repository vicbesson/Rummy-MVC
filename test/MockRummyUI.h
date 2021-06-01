#ifndef MOCKRUMMYUI_H_INCLUDED
#define MOCKRUMMYUI_H_INCLUDED

#include <list>
#include <vector>
#include "RummyUI.h"
#include "Player.h"
#include "Card.h"
#include "gmock/gmock.h"

class MockRummyUI : public RummyUI {
 public:
  explicit MockRummyUI() {}
  virtual ~MockRummyUI() {}
  MOCK_METHOD1(pickMeld, unsigned int(std::vector<std::list<Card*>>));
  MOCK_METHOD1(requestCard, unsigned int(std::list<Card*>*));
  MOCK_METHOD0(playFailed, void());
  MOCK_METHOD0(playSucceeded, void());
  MOCK_METHOD1(wantToMeld, bool(std::vector<std::list<Card*>>));
  MOCK_METHOD1(chooseMeld, unsigned int(std::vector<std::list<Card*>>));
  MOCK_METHOD1(chooseDraw, bool(Card*));
  MOCK_METHOD1(restock, bool(Card*));
  MOCK_METHOD1(chooseDiscard, unsigned int(std::list<Card*>*));
  MOCK_METHOD1(displayPlayerHand, void(std::list<Card*>));
  MOCK_METHOD1(displayMeld, void(std::list<Card*>));
  MOCK_METHOD1(displayStartTurn, void(Player*));
  MOCK_METHOD1(displayEndTurn, void(Player*));
  MOCK_METHOD0(displayWelcomeMessage, void());
  MOCK_METHOD2(displayCardAcquired, void(Player*, Card*));
  MOCK_METHOD1(showScores, void(std::vector<Player*>));
};

#endif //MOCKRUMMYUI_H_INCLUDED
