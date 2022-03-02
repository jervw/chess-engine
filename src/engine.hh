#pragma once
#include <vector>
#include <utility>
#include <fstream>


class Engine {
public:
    Engine(Color, Board*);
    ~Engine();

    bool play();

    int mini(int depth);
    int miniAlphaBeta(int depth, int alpha, int beta);

    int maxi(int depth);
    int maxiAlphaBeta(int depth, int alpha, int beta);

    int evaluate();


private:
    Board* board;
    Color engineColor;
    std::vector<std::pair<Piece*, Tile>> moves;

    std::string movesToString(const std::vector<std::pair<Piece*, Tile>>&);

};


