#include "aiplayer.h"
#include <stack>

using std::vector;

AI::AI(gameboard& gb, bool playerxstarts, bool isplayerx)
        : playerxstarts(playerxstarts), isplayerx(isplayerx) {
    this->gb = &gb;
    buildstatetree();
    assignminimaxvalues();
}

AI::~AI() {
    std::stack<State*> statestack;
    statestack.push(root);
    while (!statestack.empty()) {
        State* temp = statestack.top();
        statestack.pop();
        for (int i = 0; i < 9; i++) {
            if (temp->children[i] != nullptr) {
                statestack.push(temp->children[i]);
            }
        }
        delete temp;
    }
}

void AI::buildstatetree() {
    currentnode->xplayersturn = playerxstarts;
    for (size_t i = 0; i < 9; i++) {
        currentnode->children[i] = new State;
    }
    std::stack<State*> statestack;
    statestack.push(currentnode);
    while (!statestack.empty()) {
        State* poppedstate = statestack.top();
        statestack.pop();
        for (size_t i = 0; i < 9; i++) {
            State* child = poppedstate->children[i];
            if (child == nullptr) {
                continue;
            }
            for (size_t k = 0; k < 9; k++) {
                if (poppedstate->children[k] != nullptr && k != i) {
                    child->children[k] = new State;
                } else {
                    child->children[k] = nullptr;
                }
            }
            child->xplayersturn = !poppedstate->xplayersturn;
            statestack.push(child);
        }
    }
}

void AI::assignminimaxvalues() {
    gameboard simulationboard;
    assignminimaxvalues(root, simulationboard);
}

void AI::assignminimaxvalues(State* s, gameboard& gb) {
    bool lastmovewon = checkwin(gb, !s->xplayersturn);
    if (lastmovewon) {
        if (isplayerx ^ s->xplayersturn) {
            s->minimaxval = 1;
        } else {
            s->minimaxval = -1;
        }
    } else {
        s->minimaxval = 0;
        for (int i = 0; i < 9; i++) {
            if (s->children[i] != nullptr) {
                gb[i] = s->xplayersturn;
                assignminimaxvalues(s->children[i], gb);
                gb[i] = EMPTY;
            }
        }
    }
}

void AI::debugprint() {
    State* s = currentnode;
    for (int i = 0; i < 9; i++) {
        std::cout << (s->xplayersturn ? X : O) << ": ";
        for (int j = 0; j < 9; j++) {
            if (s->children[j] != nullptr) {
                std::cout << j << " ";
            }
        }
        std::cout << std::endl;
        s = s->children[i];
    }
}

void AI::informplayersmove(size_t row, size_t col) {
    currentnode = currentnode->children[row + 3 * col];
} 
