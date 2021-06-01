#include <vector>
#include <random>
#include <algorithm>
#include "Deck.h"

Deck::~Deck() {
  for (Card* c : deck) {
    delete c;
  }
  deck.clear();
}

void Deck::addCard(Card* card) {
    deck.push_back(card);
}

void Deck::createStandard() {
    std::vector<Card::Suit> suits;
    suits.push_back(Card::CLUB);
    suits.push_back(Card::DIAMOND);
    suits.push_back(Card::SPADE);
    suits.push_back(Card::HEART);

    std::vector<Card::Rank> ranks;
    ranks.push_back(Card::ACE);
    ranks.push_back(Card::TWO);
    ranks.push_back(Card::THREE);
    ranks.push_back(Card::FOUR);
    ranks.push_back(Card::FIVE);
    ranks.push_back(Card::SIX);
    ranks.push_back(Card::SEVEN);
    ranks.push_back(Card::EIGHT);
    ranks.push_back(Card::NINE);
    ranks.push_back(Card::TEN);
    ranks.push_back(Card::JACK);
    ranks.push_back(Card::QUEEN);
    ranks.push_back(Card::KING);

    for (std::vector<Card::Suit>::iterator suit = suits.begin();
            suit != suits.end(); ++suit)
        for (std::vector<Card::Rank>::iterator rank = ranks.begin();
                rank != ranks.end();
                ++rank)
            addCard(new Card(*suit, *rank));
}

Card* Deck::getCard() {
    if (deck.empty())
        return nullptr;

    Card* card = deck.front();
    deck.erase(deck.begin());
    return card;
}

void Deck::shuffle() {
    std::random_shuffle(deck.begin(), deck.end());
}

unsigned int Deck::size() {
    return deck.size();
}
