#pragma once
#include "board.hh"

class Player {
public:
    virtual Move getMove() = 0;
    bool getColor();
    void setBoard(Board*);

protected:
    void removeCheckedMoves(std::vector<Move>&);
    Board* getBoard();
    void setColor(bool);

private:
    Board* board;
    bool color;
};
