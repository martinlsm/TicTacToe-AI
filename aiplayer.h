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
    ~AI() { }
    void informplayersmove(size_t row, size_t col);
    void makemove();
    void debugprint();
private:
    bool playerxstarts;
    bool isplayerx;
    gameboard* gb;
    struct State {
        bool xplayersturn;
        map<size_t, State*> children;
        int minimaxval = -2;
    };
    State* currentnode = new State;
    void buildnodetree();
    void debugfillstates(State* s);
};


#endif
