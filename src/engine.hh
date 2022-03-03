#pragma once
#include <vector>
#include <utility>
#include "game.hh"
#include "minmax.hh"



class Engine {
public:
    Engine(Color, Board*);
    ~Engine();

    bool play();
    bool generateMoves();

    double evaluate();
    int search(int depth, int alpha, int beta);

    int minimax(int depth);

    double materialScore();


private:
    Board* board;
    Color engineColor;
    std::vector<std::pair<Piece*, Tile>> moves;

    std::string movesToString(const std::vector<std::pair<Piece*, Tile>>&);

};


