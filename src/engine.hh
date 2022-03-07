#pragma once
#include "player.hh"
#include <limits>
#include <algorithm>

class Engine : public Player {

public:
    Engine(bool, int);
    Move promptMove();

private:
    int depth; // depth for minimax algorithm
    std::vector<std::string> buffer; // move buffer

    Move search(int, int);
    int negamax(Board*, int, int, int, bool);
    int evaluate(Board*);
    void printData(int, int);
};
