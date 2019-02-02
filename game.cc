#include <iostream>
#include <regex>
#include <cstdlib>
#include <time.h>
#include "gameboard.h"
#include "aiplayer.h"

using std::string;

void playround() {
    gameboard gb;
    srand(time(NULL));
    bool xiscurrentplayer = rand() % 2;
    bool AI_is_x = true;
    AI ai(gb, xiscurrentplayer, AI_is_x);
    for (int i = 0; i < 9; i++) gb[i] = EMPTY;

    for (int turn_nbr = 1; turn_nbr <= 9; turn_nbr++) {
        if (!(xiscurrentplayer ^ AI_is_x)) {
            ai.makemove();
        } else {
            printboard(gb, std::cout);
            std::cout << "Choose a tile (" << (xiscurrentplayer ? X : O)
                    << "):" << std::endl;
            while (true) {
                try {
                    string rowstr, colstr;
                    std::cin >> rowstr >> colstr;
                    std::regex reg("[1-3]");
                    if (!regex_match(rowstr, reg) || !regex_match(colstr, reg)) {
                        std::cout << "Not a valid matrix index" << std::endl;
                        continue;
                    }
                    size_t row = std::stoi(rowstr) - 1;
                    size_t col = std::stoi(colstr) - 1;
                    makemove(gb, row, col, !AI_is_x);
                    printboard(gb, std::cout);
                    ai.informplayersmove(row, col);
                } catch (const std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
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
    printboard(gb, std::cout);
    std::cout << "It's a tie." << std::endl;
}

int main() {
    playround();
}
