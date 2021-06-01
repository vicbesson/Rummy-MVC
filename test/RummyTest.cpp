#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MockDeck.h"
#include "MockRummyUI.h"

#include "Card.h"
#include "Rummy.h"
#include "Game.h"
#include "Player.h"

using namespace ::testing;//NOLINT

TEST(RummyTest, CardDealSmall) {
  MockDeck* d = new MockDeck();
  Expectation size =
  EXPECT_CALL(*d, size())
  .Times(1)
  .WillOnce(Return(21));
  EXPECT_CALL(*d, getCard())
  .Times(21)
  .After(size)
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)));
  MockRummyUI* ui = new MockRummyUI();
  EXPECT_CALL(*ui, displayWelcomeMessage())
  .Times(1)
  .WillOnce(Return());
  Game* game = new Rummy(ui, d);
  game->addPlayer(new Player("cpu1"));
  game->addPlayer(new Player("cpu2"));
  game->dealCards(game->getPlayers());
  for (Player* p : game->getPlayers())
      EXPECT_EQ(10, p->getHand()->size());
  delete game;
}

TEST(RummyTest, CardDealMedium) {
  MockDeck* d = new MockDeck();
  Expectation size =
  EXPECT_CALL(*d, size())
  .Times(1)
  .WillOnce(Return(22));
  EXPECT_CALL(*d, getCard())
  .Times(22)
  .After(size)
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)));
  MockRummyUI* ui = new MockRummyUI();
  EXPECT_CALL(*ui, displayWelcomeMessage())
  .Times(1)
  .WillOnce(Return());
  Game* game = new Rummy(ui, d);
  game->addPlayer(new Player("cpu1"));
  game->addPlayer(new Player("cpu2"));
  game->addPlayer(new Player("cpu3"));
  game->dealCards(game->getPlayers());
  for (Player* p : game->getPlayers())
      EXPECT_EQ(7, p->getHand()->size());
  delete game;
}

TEST(RummyTest, CardDealLarge) {
  MockDeck* d = new MockDeck();
  Expectation size =
  EXPECT_CALL(*d, size())
  .Times(1)
  .WillOnce(Return(31));
  EXPECT_CALL(*d, getCard())
  .Times(31)
  .After(size)
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)));
  MockRummyUI* ui = new MockRummyUI();
  EXPECT_CALL(*ui, displayWelcomeMessage())
  .Times(1)
  .WillOnce(Return());
  Game* game = new Rummy(ui, d);
  game->addPlayer(new Player("cpu1"));
  game->addPlayer(new Player("cpu2"));
  game->addPlayer(new Player("cpu3"));
  game->addPlayer(new Player("cpu4"));
  game->addPlayer(new Player("cpu5"));
  game->dealCards(game->getPlayers());
  for (Player* p : game->getPlayers())
      EXPECT_EQ(6, p->getHand()->size());
  delete game;
}

TEST(RummyTest, TurnOver) {
  MockDeck* d = new MockDeck();
  MockRummyUI* ui = new MockRummyUI();
  Game* game = new Rummy(ui, d);
  EXPECT_TRUE(game->turnOver());
  delete game;
}

TEST(RummyTest, IsOverTrue) {
  MockDeck* d = new MockDeck();
  MockRummyUI* ui = new MockRummyUI();
  Game* game = new Rummy(ui, d);
  game->addPlayer(new Player("cpu1"));
  game->addPlayer(new Player("cpu2"));
  EXPECT_TRUE(game->isOver());
  delete game;
}

TEST(RummyTest, IsOverFalse) {
  MockDeck* d = new MockDeck();
  Expectation size =
  EXPECT_CALL(*d, size())
  .Times(1)
  .WillOnce(Return(21));
  EXPECT_CALL(*d, getCard())
  .Times(21)
  .After(size)
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)))
  .WillOnce(Return(new Card(Card::CLUB, Card::ACE)));
  MockRummyUI* ui = new MockRummyUI();
  EXPECT_CALL(*ui, displayWelcomeMessage())
  .Times(1)
  .WillOnce(Return());
  Game* game = new Rummy(ui, d);
  game->addPlayer(new Player("cpu1"));
  game->addPlayer(new Player("cpu2"));
  game->dealCards(game->getPlayers());
  EXPECT_FALSE(game->isOver());
  delete game;
}
