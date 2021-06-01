#ifndef MOCKDECK_H_INCLUDED
#define MOCKDECK_H_INCLUDED

#include "gmock/gmock.h"
#include "../include/Deck.h"
#include "../include/Card.h"

class MockDeck : public Deck {
 public:
    explicit MockDeck() {}
    virtual ~MockDeck() {}

    MOCK_METHOD0(getCard, Card*());
    MOCK_METHOD0(size, unsigned int());
    MOCK_METHOD0(shuffle, void());
};

#endif // MOCKDECK_H_INCLUDED
