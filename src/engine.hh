#pragma once
#include "player.hh"
#include <limits.h>
#include <algorithm>
#include <vector>
#include <string>

class Engine : public Player {

public:
    Engine(bool, int);
    Move play();

private:
    int depth;
    std::vector<std::string> buffer; // move buffer

    Move search(int, int);
    int negamax(Board*, int, int, int, bool);
    int evaluate(Board*);
};
