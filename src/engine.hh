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

    double mini(int depth);
    double miniAlphaBeta(int depth, int alpha, int beta);

    double maxi(int depth);
    double maxiAlphaBeta(int depth, int alpha, int beta);


    double evaluate();

    double materialScore();


private:
    Board* board;
    Color engineColor;
    std::vector<std::pair<Piece*, Tile>> moves;

    std::string movesToString(const std::vector<std::pair<Piece*, Tile>>&);

};


