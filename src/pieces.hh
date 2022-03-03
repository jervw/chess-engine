#pragma once

#include <string>
#include <vector>
#include <cmath>    
#include "tile.hh"
#include "board.hh"

class Board;

enum Color { NO_COLOR, WHITE, BLACK };

class Piece {
public:
    Piece(int, int, Color, Board*);
    std::string getName();
    char getSymbol();
    int getRow();
    int getCol();
    int getMatValue();
    bool getMoved();
    void setMoved(bool);
    void move(int, int);
    Color getPlayer();
    std::vector<Tile> getPossibleTiles(Board&);

    //debug
    std::string pieceInfo();

    virtual bool possibleMove(int, int) = 0; // start and end position.
    virtual bool legalMove(int, int, Board&) = 0; // based on the positions of other pieces.
    virtual int getTileValue(int, int) = 0;

protected:
    Board* board;
    std::string name;
    char symbol;
    int row, col;
    int matValue;
    Color player;
    bool moved;
};

class Rook : public Piece {
public:
    Rook(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    int getTileValue(int, int);
};

class Knight : public Piece {
public:
    Knight(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    int getTileValue(int, int);
};

class Bishop : public Piece {
public:
    Bishop(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    int getTileValue(int, int);
};

class Queen : public Piece {

public:
    Queen(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    int getTileValue(int, int);
};

class King : public Piece {
public:
    King(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    int getTileValue(int, int);
};

class Pawn : public Piece {
public:
    Pawn(int, int, Color, Board*);
    bool possibleMove(int, int);
    bool legalMove(int, int, Board&);
    bool checkAttack(int, int);
    int getTileValue(int, int);
};


