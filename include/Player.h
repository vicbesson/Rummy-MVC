#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <string>
#include <list>

class Player {
 public:
    explicit Player(const std::string& n) : name(n) {}
    virtual ~Player();
    void addCard(Card* c);
    Card* getCard(unsigned int index);
    std::list<Card*>* getHand();
    void addPoints(unsigned int points);
    unsigned int getScore();

    const std::string name;

 private:
    std::list<Card*> hand;
    unsigned int score = 0;
};

#endif // PLAYER_H
