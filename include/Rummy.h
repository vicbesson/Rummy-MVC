/**
* @class Rummy
* @brief
* This class is meant to act as the controller for the Rummy game.
* @author $Author: Victor Besson $
*/

#ifndef RUMMY_H
#define RUMMY_H

#include "Game.h"
#include <vector>
#include <list>

class Rummy : public Game {
 public:
  /**
  * Constructor.
  * @param ui The view to be used for Rummy.
  * @param d The deck to be used in Rummy.
  */
  Rummy(GameUI* ui, Deck* d) : Game(ui, d) {}
  /**
  * Destructor.
  * Deletes and clears: melds and discard.
  * Clears: possibleMelds.
  */
  virtual ~Rummy();
  /**
  * Deals cards to players based on rules from
  * https://bicyclecards.com/how-to-play/rummy-rum/
  */
  void dealCards(std::vector<Player*> p);
  /**
  * The bread and butter of the game. Includes all of the gameplay except
  * discarding card at end of turn.
  * Check cpp comments for more info.
  * @param playerNum The index of the player whose current turn it is.
  * @param numPlayers The number of players currently in the game.
  */
  void beforeCardPlayed(unsigned int playerNum, unsigned int numPlayers);
  /**
  * This function incorporates the discard functionality of rummy.
  * @param currentPlayer The current player whose turn it is.
  * @param players The players that are in the game.
  * @param played The card that was requested in the game start loop.
  */
  void afterCardPlayed(Player* currentPlayer, std::vector<Player*> players,
                       Card* played);
  /**
  * Overidded function for turnOver, just returns true.
  * @return Will return false never and only true.
  */
  bool turnOver();
  /**
  * Checks if the game is completed, based on if a players hand is empty.
  * @return Will return true if a player has an empty hand else will return false.
  */
  bool isOver() const;

 private:
  /**
  * Initial hand size for players if game is less than 3.
  */
  const unsigned int NUM_CARDS_SMALL = 10;
  /**
  * Initial hand size for players if game is less than 5.
  */
  const unsigned int NUM_CARDS_MEDIUM = 7;
  /**
  * Initial hand size for players if game is 5 or greater.
  */
  const unsigned int NUM_CARDS_LARGE = 6;
  /**
  * List used as the discard pile in the game Rummy.
  */
  std::list<Card*> discard;
  /**
  * Vector of lists used for players melds in the game Rummy.
  */
  std::vector<std::list<Card*>> melds;
  /**
  * Vector of vector of lists of cards for the possible melds each player has.
  */
  std::vector<std::vector<std::list<Card*>>> possibleMelds;
  /**
  * Function that checks the players hand for all possible melds and adds them
  * to the possibleMelds vector for that player.
  * @param hand The hand of the player we are checking.
  * @param playerNum The index of the current player in players. Used to adds
  * possibleMeld to the that players possibleMelds.
  * @return Will return true if melds exist, false if they do not.
  */
  bool checkForMelds(std::list<Card*>* hand, unsigned int playerNum);
  /**
  * Checks if the players remaining cards are matching
  * @param hand The hand of the player we are checking.
  * @return Will return true if they are matching else will return false.
  */
  bool completeMeld(std::list<Card*>* hand);
  /**
  * Removes card from hand if it can be added to meld
  * @param hand The hand of the player we are checking.
  * @param meld The meld we are checking.
  * @return The card that will be added to meld.
  */
  Card* addToMeld(std::list<Card*>* hand, std::list<Card*> meld);
  /**
  * Gets the score value of a card.
  * @param c The card to get score for.
  * @return The score value for the card.
  */
  unsigned int pipValue(Card* c) const;
  /**
  * The functionality for laying off cards into melds.
  * @param hand The hand of the player we are using.
  * @param players The players in the game.
  */
  void layingOff(std::list<Card*>* hand, std::vector<Player*> players);
  /**
  * Checks if a vector contains a particular rank of card.
  * @param list The vector to check.
  * @param x The rank to check for.
  */
  bool containsRank(const std::vector<Card::Rank>& list, Card::Rank x);
  /**
  * Checks if a vector contains a particular card.
  * @param list The vector to check.
  * @param x The card to check for.
  */
  bool containsCard(const std::vector<Card*>& list, Card* x);
  /**
  * Boolean value for if the deck is empty. Used for restock.
  */
  bool DeckEmpty = false;
};

#endif // RUMMY_H
