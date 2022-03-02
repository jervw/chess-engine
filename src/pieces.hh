#pragma once

#include <vector>
#include <cmath>    
#include "tile.hh"
#include "board.hh"

class Board;

enum Color { NO_COLOR, WHITE, BLACK };

class Piece {
public:
    Piece(int, int, Color, Board*);
    char getSymbol();
    int getRow();
    int getCol();
    int getValue();
    bool getMoved();
    void setMoved(bool);
    void move(int, int);
    Color getPlayer();
    std::vector<Tile> getPossibleTiles(Board&);

    virtual bool possibleMove(int, int) = 0; // start and end position.
    virtual bool legalMove(int, int, Board&) = 0; // based on the positions of other pieces.

protected:
    Board* board;
    char symbol;
    int row, col;
    int value;
    Color player;
    bool moved;
};

class Rook : public Piece {
public:
    Rook(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
};

class Knight : public Piece {
public:
    Knight(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
};

class Bishop : public Piece {
public:
    Bishop(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
};

class Queen : public Piece {

public:
    Queen(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
};

class King : public Piece {
public:
    King(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
};

class Pawn : public Piece {
public:
    Pawn(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    bool checkAttack(int, int);
};


