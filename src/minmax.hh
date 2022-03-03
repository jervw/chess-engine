#pragma once

#include <utility>
#include "pieces.hh"
#include "tile.hh"

class MinMax {
public:
    MinMax(double eval, std::pair<Piece*, Tile> move) : eval(eval), move(move) {};
    MinMax();

    double eval;
    std::pair<Piece*, Tile> move;
};
