#include <iostream>
#include <vector>
#include "GameUI.h"

unsigned int GameUI::choosePlayer(unsigned int playerNum,
                                  unsigned int numPlayers) {
    unsigned int selection = playerNum;
    std::cout << "You are Player #" << playerNum << std::endl;
    while (selection == playerNum || selection >= numPlayers) {
        std::cout << "Which player (0-" << numPlayers-1 << ")? ";
        std::cin >> selection;
        if (selection == playerNum)
            std::cout << "That is you! Please choose another player."
              << std::endl;
        if (selection >= numPlayers)
            std::cout << "Player #" << selection <<
                 " doesn't exist! Please choose another player." << std::endl;
    }
    return selection;
}

void GameUI::showScores(std::vector<Player*> players) {
    std::cout << "---- Scores ----" << std::endl;
    for (Player* player : players)
        std::cout << player->name << ": " << player->getScore() << std::endl;
}
