#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MockDeck.h"
#include "MockUI.h"

#include "Card.h"
#include "Game.h"
#include "GoFish.h"
#include "Player.h"

using ::testing::Return;//NOLINT
using ::testing::_;//NOLINT
using ::testing::Expectation;//NOLINT

TEST(GoFishTest, CardDealSmall) {
    MockDeck* d = new MockDeck();
    Expectation size =
    EXPECT_CALL(*d, size())
    .Times(1)
    .WillOnce(Return(14));

    EXPECT_CALL(*d, getCard())
    .Times(14)
    .After(size)
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)));



    MockUI* ui = new MockUI();
    Game* game = new GoFish(ui, d);

    game->addPlayer(new Player("John"));
    game->addPlayer(new Player("Danielle"));

    game->dealCards(game->getPlayers());

    for (Player* p : game->getPlayers())
        EXPECT_EQ(7, p->getHand()->size());
    delete game;
}


TEST(GoFishTest, CardDealLarge) {
    MockDeck* d = new MockDeck();

    EXPECT_CALL(*d, size())
    .Times(1)
    .WillOnce(Return(20));

    EXPECT_CALL(*d, getCard())
    .Times(20)
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)))
    .WillOnce(Return(new Card(Card::DIAMOND, Card::ACE)));

    MockUI* ui = new MockUI();

    Game* game = new GoFish(ui, d);

    game->addPlayer(new Player("John"));
    game->addPlayer(new Player("Danielle"));
    game->addPlayer(new Player("Tara"));
    game->addPlayer(new Player("Erik"));

    game->dealCards(game->getPlayers());

    for (Player* p : game->getPlayers())
        EXPECT_EQ(5, p->getHand()->size());
    delete game;
}

TEST(GoFishTest, DrawSet) {
    MockDeck* d = new MockDeck();
    Expectation shuffle =
    EXPECT_CALL(*d, shuffle());
    EXPECT_CALL(*d, getCard())
    .Times(23)
    .After(shuffle)
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))
    .WillOnce(Return(new Card(Card::CLUB, Card::THREE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::JACK)))
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))
    .WillOnce(Return(new Card(Card::CLUB, Card::THREE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::JACK)))
    .WillOnce(Return(new Card(Card::CLUB, Card::THREE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::JACK)))
    .WillOnce(Return(new Card(Card::CLUB, Card::THREE)));

    EXPECT_CALL(*d, size())
    .Times(1)
    .WillOnce(Return(23));

    MockUI* ui = new MockUI();

    EXPECT_CALL(*ui, choosePlayer(_ , _))
    .Times(9)
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1));

    EXPECT_CALL(*ui, playFailed())
    .Times(9);

    EXPECT_CALL(*ui, requestCard(_))
    .Times(9);

    EXPECT_CALL(*ui, showScores(_))
    .Times(1);

    Game* game = new GoFish(ui, d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->start();

    EXPECT_EQ(3, player1->getScore());
    delete game;
}

TEST(GoFishTest, AfterCardPlayedSet) {
    MockDeck* d = new MockDeck();

    Expectation deckShuffled = EXPECT_CALL(*d, shuffle());

    EXPECT_CALL(*d, getCard())
    .Times(15)
    //.After(EXPECT_CALL(d, shuffle()))
    // Hands
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))

    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)))
    .WillOnce(Return(new Card(Card::CLUB, Card::QUEEN)))

    .WillOnce(Return(new Card(Card::CLUB, Card::KING)))
    .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))

    // Deck
    .WillOnce(Return(new Card(Card::CLUB, Card::TWO)));

    EXPECT_CALL(*d, size())
    .Times(1)
    .WillOnce(Return(15));

    MockUI* ui = new MockUI();

    EXPECT_CALL(*ui, choosePlayer(_, _))
    .Times(3)
    .WillOnce(Return(1))
    .WillOnce(Return(0))
    .WillOnce(Return(1));

    EXPECT_CALL(*ui, playFailed())
    .Times(1);

    EXPECT_CALL(*ui, playSucceeded())
    .Times(2);

    EXPECT_CALL(*ui, requestCard(_))
    .Times(3);

    EXPECT_CALL(*ui, showScores(_))
    .Times(1);


    Game* game = new GoFish(ui, d);

    Player* player1 = new Player("John");
    Player* player2 = new Player("Kira");

    game->addPlayer(player1);
    game->addPlayer(player2);
    game->start();

    EXPECT_EQ(2, player1->getScore());
    delete game;
}
