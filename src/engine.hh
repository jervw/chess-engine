#pragma once
#include <vector>
#include <utility>
#include "game.hh"



class Engine {
public:
    Engine(Color, Board*);
    ~Engine();

    bool play();
    bool generateMoves();

    double evaluate();

    int minimax(int depth);

    double materialScore();


private:
    Board* board;
    Color engineColor;
    std::vector<std::pair<Piece*, Tile>> moves;

    void movesToString(const std::vector<std::pair<Piece*, Tile>>&);

};


