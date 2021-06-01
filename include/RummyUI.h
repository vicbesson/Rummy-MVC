/**
* @class RummyUI
* @brief
* This class is meant to act as the view for the Rummy game.
* @author $Author: Victor Besson $
*/

#ifndef RUMMYUI_H
#define RUMMYUI_H

#include "GameUI.h"
#include "Card.h"
#include "Player.h"
#include <list>
#include <vector>

class RummyUI : public GameUI {
 public:
  /**
  * Constructor.
  */
  RummyUI() {}
  /**
  * Destructor.
  */
  virtual ~RummyUI() {}
  /**
  * Allows the player to pick a meld to layoff on.
  * @param melds The melds for the player to choose to layoff on.
  * @return The index of the meld the player wants to layoff on.
  */
  virtual unsigned int pickMeld(std::vector<std::list<Card*>> melds);
  /**
  * Literally does nothing but return 0 because it is used in game and cannnot
  * be implemented properly into Rummy.
  * @param hand The hand to be used
  * @return Only return 0.
  */
  virtual unsigned int requestCard(std::list<Card*>* hand);
  /**
  * Tells player play failed.
  */
  virtual void playFailed();
  /**
  * Tells player play succeeded.
  */
  virtual void playSucceeded();
  /**
  * Shows the player their possible melds and asks if they want to make a meld.
  * @param possibleMelds The players possible melds to choose from.
  * @return Will return true if the player chooses to make meld, will return
  * false if they do not want to.
  */
  virtual bool wantToMeld(std::vector<std::list<Card*>> possibleMelds);
  /**
  * Shows the player their possible melds and asks them to choose one for their meld.
  * @param possibleMelds The players possible melds to choose from.
  * @return The index of the possibleMeld the player chose.
  */
  virtual unsigned int chooseMeld(std::vector<std::list<Card*>>
    possibleMelds);
  /**
  * Asks the player if they would like to draw from the deck or the discard pile.
  * @param c The top of the discard pile.
  * @return Will return true if they choose to draw from discard, will return
  * true if they want to draw from the deck.
  */
  virtual bool chooseDraw(Card* c);
  /**
  * Asks the player if they want to restock the deck with the discard pile.
  * @param c The top of the discard pile.
  * @return Will return true if they player wants to restock, false otherwise.
  */
  virtual bool restock(Card* c);
  /**
  * Asks the player to choose a card to discard.
  * @param hand The players hand.
  * @return The index of the card they want to discard.
  */
  virtual unsigned int chooseDiscard(std::list<Card*>* hand);
  /**
  * Displays a players hand.
  * @param hand The hand to be displayed.
  */
  virtual void displayPlayerHand(std::list<Card*>* hand);
  /**
  * Displays a players meld.
  * @param meld The meld to be displayed.
  */
  virtual void displayMeld(std::list<Card*> meld);
  /**
  * Displays and shows that it is a new players turn.
  * @param p The player used to display name.
  */
  virtual void displayStartTurn(Player* p);
  /**
  * Displays and shows that the turn is over.
  * @param p The player used to display name.
  */
  virtual void displayEndTurn(Player* p);
  /**
  * Message displayed at game start.
  */
  virtual void displayWelcomeMessage();
  /**
  * Displays the cards that were removed and added to meld.
  * @param cards The cards that were added to meld.
  */
  virtual void displayCardsAddedToMeld(std::list<Card*> cards);
  /**
  * Displays a card that the player acquired.
  * @param p The player who acquired the card.
  * @param c The card that was acquired.
  */
  virtual void displayCardAcquired(Player* p, Card* c);
  /**
  * Displays ending messages, names of players, and scores.
  * @param players The players used to display names and scores.
  */
  virtual void showScores(std::vector<Player*> players);
};

#endif // RUMMYUI_H
