#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>

using tilestate = unsigned char;
const tilestate EMPTY = 'E';
const tilestate X     = 'X';
const tilestate O     = 'O';

using gameboard = tilestate[9];

void makemove(gameboard& gb, size_t row, size_t col, bool xplayersturn);

void cleartile(gameboard& gb, size_t row, size_t col);

bool checkwin(gameboard& gb, bool xplayer);

void printboard(gameboard& gb, std::ostream& os);

size_t boardindexconvert(const std::string& str);

void makemovefromcommand(gameboard& gb, bool xplayer, std::istream& is);


#endif
