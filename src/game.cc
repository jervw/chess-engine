#include "game.hh"



Game::Game(int humanColor)
{
    _humanColor = humanColor;
    _engineColor = 1 - humanColor;
}


