#include <iostream>
#include "gameboard.h"
#include "aiplayer.h"


void playround() {
    gameboard gb;
    bool xiscurrentplayer = true;
    bool AI_is_x = true;
    AI ai(gb, xiscurrentplayer, AI_is_x);
    ai.debugprint(); 
    for (int i = 0; i < 9; i++) gb[i] = EMPTY;
    printboard(gb, std::cout);
    for (int turn_nbr = 1; turn_nbr <= 9; turn_nbr++) {
        std::cout << "Choose a tile (" << (xiscurrentplayer ? X : O)
                << "):" << std::endl;
        while (true) {
            try {
                makemovefromcommand(gb, xiscurrentplayer, std::cin);
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid matrix index, try again." << std::endl;
                continue;
            }
            printboard(gb, std::cout);
            break;
        }
        xiscurrentplayer = !xiscurrentplayer;
    }
}

int main() {
    playround();
}
