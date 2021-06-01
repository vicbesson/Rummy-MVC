#include <list>
#include <vector>
#include "GoFish.h"

bool hasSet(std::list<Card*>* hand);

void GoFish::dealCards(std::vector<Player*> players) {
    unsigned int numCards;
    if (players.size() < 4)
        numCards = NUM_CARDS_SMALL;
    else
        numCards = NUM_CARDS_LARGE;

    unsigned int deckSize = deck->size();
    unsigned int neededCards = players.size() * numCards;

    if (deckSize >= neededCards) {
        unsigned int playerNum = 0;
        for (unsigned int i = 0; i < neededCards; i++) {
            Player* p = players.at(playerNum);
            p->addCard(deck->getCard());
            playerNum = (++playerNum) % players.size();
        }
    }
}

void GoFish::beforeCardPlayed(unsigned int playerNum,
                              unsigned int numPlayers) {
    playerAsked = ui->choosePlayer(playerNum, numPlayers);
}

void GoFish::afterCardPlayed(Player* currentPlayer,
                             std::vector<Player*> players,
                             Card* played) {
    std::list<Card*>* hand = players.at(playerAsked)->getHand();
    std::list<Card*>::iterator card;
    std::list<Card*> toRemove;
    for (card = hand->begin(); card != hand->end(); ++card) {
        if ((*card)->rank == played->rank) {
            currentPlayer->getHand()->push_back(*card);
            toRemove.push_back(*card);
        }
    }

    if (toRemove.size() > 0) {
        ui->playSucceeded();
        for (std::list<Card*>::iterator card = toRemove.begin();
                card != toRemove.end();
                ++card)
            hand->remove(*card);

        // Check if have a set of cards
        if (hasSet(currentPlayer->getHand())) {
            currentPlayer->addPoints(1);
        }
    } else {
        ui->playFailed();
        Card* c = deck->getCard();
        currentPlayer->addCard(c);
        if (hasSet(currentPlayer->getHand())) {
            currentPlayer->addPoints(1);
        }
    }
}

bool hasSet(std::list<Card*>* hand) {
    std::list<Card*> toRemove;
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

        if (count == 4) {
            for (std::list<Card*>::iterator card = toRemove.begin();
                    card != toRemove.end();
                    ++card) {
                Card* c = *card;
                hand->remove(*card);
                delete c;
            }
            return true;
        }
    }
    return false;
}

bool GoFish::turnOver() {
    return true;
}
