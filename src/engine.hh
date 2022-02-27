#pragma once
#include <vector>
#include <utility>
#include <fstream>


class Engine {
public:
    Engine(Color, Board*);
    ~Engine();

    bool play();

private:
    Board* board;
    Color engineColor;
    std::vector<std::pair<Piece*, Tile>> moves;

    std::string movesToString(const std::vector<std::pair<Piece*, Tile>>&);

};


