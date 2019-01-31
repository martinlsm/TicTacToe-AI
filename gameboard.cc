#include <regex>
#include "gameboard.h"


void makemove(gameboard& gb, size_t row, size_t col, bool xplayersturn) {
    gb[row + 3 * col] = xplayersturn ? X : O;
}

bool checkwin(gameboard& gb, bool xplayer) {
    tilestate p = xplayer ? X : O;

    // Check rows and cols
    for (size_t i = 0; i < 3; i++) {
        if ((gb[3*i] == p && gb[3*i+1] == p && gb[3*i+2] == p)
        ||  (gb[i] == p && gb[i+3] == p &&  gb[i+6] == p))
        {
            return true;
        }
    }

    // Check diagonals
    if ((gb[2] == p && gb[4] == p && gb[6] == p)
    ||  (gb[0] == p && gb[4] == p && gb[8] == p))
    {
        return true;
    }
    return false;
}

void printboard(gameboard& gb, std::ostream& os) {
    for (size_t r = 0; r < 3; r++) {
        os << "    ";
        for (size_t c = 0; c < 3; c++) {

            os << gb[r + 3 * c] << "  ";
        }
        os << "\n";
    }
}

size_t boardindexconvert(const std::string& str) {
    if (std::regex_match(str, std::regex("[1-3]"))) {
        return std::stoi(str);
    }
    throw std::invalid_argument("Not a valid matrix index");
}

void makemovefromcommand(gameboard& gb, bool xplayer, std::istream& is) {
    size_t row, col;
    is >> row >> col;
    row--;
    col--;
    if (row >= 3 || col >= 3) {
        throw std::invalid_argument("Not a valid matrix index");
    }
    if (gb[row + 3 * col] != EMPTY) {
        throw std::invalid_argument("Spot already taken");
    }
    makemove(gb, row, col, xplayer);
}
