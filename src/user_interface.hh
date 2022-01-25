#pragma once
#include "state.hh"
#include "pawn.hh"
#include "game.hh"
#include "move.hh" 


class UserInterface
{
public:
    void SetState(State* state) { this->_state = state; }
    void DrawBoard();
    Move GiveOpponentMove();
    int AskPlayerSide();

    static UserInterface* Instance();

private:
    State* _state;
    static UserInterface* instance;

    UserInterface() {}
    UserInterface(State* state) { this->_state = state; }

    int ReturnCharIndex(char&);
};
