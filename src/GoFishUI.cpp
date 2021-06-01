#include <iostream>
#include <list>
#include "GoFishUI.h"

unsigned int GoFishUI::requestCard(std::list<Card*>* hand) {
    std::cout << "Your hand:" << std::endl;
    unsigned int index = 0;
    for (std::list<Card*>::iterator i = hand->begin(); i != hand->end(); ++i) {
        Card::Rank r = (*i)->rank;
        std::cout << "\tChoice " << (++index) << ": "
          << Card::getRank(r) << std::endl;
    }
    std::cout << "Select a choice: ";

    unsigned int selection;
    std::cin >> selection;

    return selection-1;
}

void GoFishUI::playFailed() {
    std::cout << "Go Fish!" << std::endl;
}

void GoFishUI::playSucceeded() {
    std::cout << "The player had some of those cards!" << std::endl;
}
