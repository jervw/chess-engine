#include "piece.hh"
#include "params.hh"

Piece::Piece(bool color, unsigned value, char type) : color(color), value(value), hasMoved(false) {
  setType(type);
}

Piece::~Piece() {}

int Piece::getSquareValue(unsigned row, unsigned col) {
  if (color) {
    // white
    switch (type) {
    case 'P': return Params::TILE_PAWN[7 - col][7 - row];
    case 'R': return Params::TILE_ROOK[7 - col][7 - row];
    case 'N': return Params::TILE_KNIGHT[7 - col][7 - row];
    case 'B': return Params::TILE_BISHOP[7 - col][7 - row];
    case 'Q': return Params::TILE_QUEEN[7 - col][7 - row];
    case 'K': return Params::TILE_KING_MID[7 - col][7 - row];

    default: return 0;
    }

  }
  else {
    // black
    switch (type) {
    case 'p': return Params::TILE_PAWN[col][row];
    case 'r': return Params::TILE_ROOK[col][row];
    case 'n': return Params::TILE_KNIGHT[col][row];
    case 'b': return Params::TILE_BISHOP[col][row];
    case 'q': return Params::TILE_QUEEN[col][row];
    case 'k': return Params::TILE_KING_MID[col][row];

    default: return 0;
    }
  }
}


bool Piece::checkInBounds(unsigned col, unsigned row) { return (row < ROWS) && (col < COLS); }
bool Piece::getMoved() { return hasMoved; }
bool Piece::getColor() { return color; }

unsigned Piece::getValue() { return value; }
char Piece::getType() { return type; }

void Piece::setMoved(bool m) { hasMoved = m; }
inline void Piece::setType(char t) { type = (getColor() == 1) ? t : t + 32; }
