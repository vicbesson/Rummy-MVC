#ifndef MOCKUI_H_INCLUDED
#define MOCKUI_H_INCLUDED

#include <list>
#include <vector>
#include "gmock/gmock.h"
#include "../include/GameUI.h"

class MockUI : public GameUI {
 public:
    explicit MockUI() {}
    virtual ~MockUI() {}

    MOCK_METHOD1(requestCard, unsigned int(std::list<Card*>* hand));
    MOCK_METHOD0(playFailed, void());
    MOCK_METHOD0(playSucceeded, void());
    MOCK_METHOD2(choosePlayer, unsigned int(unsigned int playerNum,
      unsigned int numPlayers));
    MOCK_METHOD1(showScores, void(std::vector<Player*>));
};


#endif // MOCKUI_H_INCLUDED
