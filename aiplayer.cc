#include "aiplayer.h"
#include <stack>

using std::vector;

AI::AI(gameboard& gb, bool playerxstarts, bool isplayerx)
        : playerxstarts(playerxstarts), isplayerx(isplayerx) {
    this->gb = &gb;
    buildnodetree();
}

void AI::buildnodetree() {
    currentnode->xplayersturn = playerxstarts;
    for (size_t i = 0; i < 9; i++) {
        currentnode->children[i] = new State;
    }
    std::stack<State*> statestack;
    statestack.push(currentnode);
    while (!statestack.empty()) {
        State* poppedstate = statestack.top();
        statestack.pop();
        for (const pair<size_t, State*>& child : poppedstate->children) {
            for (const pair<size_t, State*>& c : poppedstate->children) {
                if (c.first != child.first) {
                    child.second->children[c.first] = new State;
                }
            }
            child.second->xplayersturn = !poppedstate->xplayersturn;
            statestack.push(child.second);
        }
    }
}

void AI::debugprint() {
    State* temp = currentnode;
    while (temp->children.size() != 0) {
        for (auto& child : temp->children) {
            std::cout << child.first << " ";
        }
        temp = temp->children.find(0)->second;
    }
    std::cout << std::endl;
}

void AI::informplayersmove(size_t row, size_t col) {
    currentnode = currentnode->children[row + 3 * col];
} 
