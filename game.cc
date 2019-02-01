#include <iostream>
#include "gameboard.h"
#include "aiplayer.h"


void playround() {
    gameboard gb;
    bool xiscurrentplayer = true;
    bool AI_is_x = true;
    AI ai(gb, xiscurrentplayer, AI_is_x);
    for (int i = 0; i < 9; i++) gb[i] = EMPTY;
    printboard(gb, std::cout);

    for (int turn_nbr = 1; turn_nbr <= 9; turn_nbr++) {
        if (!(xiscurrentplayer ^ AI_is_x)) {
            ai.makemove();
        } else {
            printboard(gb, std::cout);
            std::cout << "Choose a tile (" << (xiscurrentplayer ? X : O)
                    << "):" << std::endl;
            while (true) {
                try {
                    size_t row, col;
                    std::cin >> row >> col;
                    row--; col--;
                    makemove(gb, row, col, !AI_is_x);
                    ai.informplayersmove(row, col);
                } catch (const std::invalid_argument& e) {
                    std::cout << "Invalid matrix index, try again." << std::endl;
                    continue;
                }
                break;
            }
        }
        if (checkwin(gb, xiscurrentplayer)) {
            printboard(gb, std::cout);
            if (!(AI_is_x ^ xiscurrentplayer)) {
                std::cout << "AI won." << std::endl;
            } else {
                std::cout << "You won!" << std::endl;
            }
            return;
        }
        xiscurrentplayer = !xiscurrentplayer;
    }
}

int main() {
    playround();
}
