#ifndef AIPLAYER_H 
#define AIPLAYER_H

#include <vector>
#include "gameboard.h"

using std::vector;

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
        State(State* parent, size_t actionindex, bool xplayersturn)
            : parent(parent), actionindex(actionindex), xplayersturn(xplayersturn) { }
        ~State();
        State * const parent;
        const size_t actionindex;
        const bool xplayersturn;
        vector<State*> children;
        int minimaxval = -2;
    };
    State* root = new State(nullptr, -1, playerxstarts);
    State* currentnode = root;
    void assignminimaxvalues();
    void assignminimaxvalues(State* s, gameboard& gb);
};


#endif
