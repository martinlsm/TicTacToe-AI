#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <vector>
#include <map>
#include <memory>
#include "gameboard.h"

using std::vector;
using std::map;
using std::pair;
using std::unique_ptr;

class AI {
public:
    AI(gameboard& gb, bool playerxstarts, bool isplayerx);
    ~AI();
    void informplayersmove(size_t row, size_t col);
    void makemove();
    void debugprint();
private:
    bool playerxstarts;
    bool isplayerx;
    gameboard* gb;
    struct State {
        bool xplayersturn;
        State* children[9];
        int minimaxval = -2;
    };
    State* root = new State;
    State* currentnode = root;
    void buildstatetree();
    void assignminimaxvalues();
    void assignminimaxvalues(State* s, gameboard& gb);
};


#endif
