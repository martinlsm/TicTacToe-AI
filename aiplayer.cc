#include "aiplayer.h"
#include "gameboard.h"

AI::AI(gameboard& gb, bool playerxstarts, bool isplayerx)
    : playerxstarts(playerxstarts), isplayerx(isplayerx) {
    this->gb = &gb;
    assignminimaxvalues();
}

void AI::assignminimaxvalues() {
    root->minimaxval = 0;
    gameboard gb;    
    for (int i = 0; i < 9; i++) gb[i] = EMPTY;
    root->children = vector<State*>();
    for (int i = 0; i < 9; i++) {
        root->children.push_back(new State(root, i, !root->xplayersturn));
    }
    for (State* s : root->children) { 
        ::makemove(gb, s->actionindex / 3, s->actionindex % 3, playerxstarts); 
        assignminimaxvalues(s, gb);
        cleartile(gb, s->actionindex / 3, s->actionindex % 3);
    }
}

void AI::assignminimaxvalues(State* s, gameboard& gb) {
    bool lastplayerwon = checkwin(gb, !s->xplayersturn);
    if (lastplayerwon) {
        if (isplayerx ^ s->xplayersturn) {
            s->minimaxval = 1;
        } else {
            s->minimaxval = -1;
        }
    } else {
        s->children = vector<State*>();
        for (size_t i = 0; i < 9; i++) {
            if (gb[i] == EMPTY) {
                s->children.push_back(new State(s, i, !s->xplayersturn));    
            }
        }
        for (State* child : s->children) {
            gb[child->actionindex] = s->xplayersturn ? X : O;
            assignminimaxvalues(child, gb);
            gb[child->actionindex] = EMPTY;
        }
        if (s->children.empty()) {
            s->minimaxval = 0;
        }
        if (!(s->xplayersturn ^ isplayerx)) {
            int max = -2;
            for (State* child : s->children) {
                max = std::max(max, child->minimaxval);
            }
        } else {
            int min = 2;
            for (State* child : s->children) {
                min = std::min(min, child->minimaxval);
            }
        }
    }
}

AI::~AI() { }

void AI::makemove() {
    if (currentnode->children.empty()) {
        std::cout << "AI cant make a move." << std::endl;
    }
    State* maxchild = currentnode->children[0];
    for (State* child : currentnode->children) {
        if (child->minimaxval > maxchild->minimaxval) {
            maxchild = child;
        }
    }
    (*gb)[maxchild->actionindex] = isplayerx ? X : O;
    currentnode = maxchild;
}

void AI::informplayersmove(size_t row, size_t col) {
    size_t index = row + 3 * col;
    for (State* child : currentnode->children) {
        if (index == child->actionindex) {
            currentnode = child;
            return;
        }
    }
    throw "AI consideres this move invalid.";
}

void AI::debugprint() {

}
