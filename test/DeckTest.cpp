#include "gtest/gtest.h"
#include "../include/Deck.h"

TEST(DeckTest, DeckSize) {
    Deck* d = new Deck();
    d->createStandard();
    EXPECT_EQ(52, d->size());
    delete d;
}

TEST(DeckTest, DeckCard) {
    Deck* d = new Deck();
    d->createStandard();
    EXPECT_EQ(52, d->size());
    delete d->getCard();
    EXPECT_EQ(51, d->size());
    delete d;
}


TEST(DeckTest, DeckShuffle) {
    Deck* d1 = new Deck();
    d1->createStandard();
    Card* c1 = d1->getCard();
    EXPECT_EQ(Card::CLUB, c1->suit);
    EXPECT_EQ(Card::ACE, c1->rank);
    d1->addCard(c1);
    Deck* d2 = new Deck();
    d2->createStandard();
    d2->shuffle();
    Card* c2 = d2->getCard();
    EXPECT_FALSE(Card::CLUB == c2->suit && Card::ACE == c2->rank);
    d2->addCard(c2);
    delete d1;
    delete d2;
}

TEST(DeckTest, DeckEmpty) {
    Deck* d = new Deck();
    unsigned int deckSize = d->size();
    for (unsigned int i=0; i < deckSize; i++) {
        delete d->getCard();
    }
    EXPECT_TRUE(d->getCard() == nullptr);
    delete d;
}
