#include "piece.hh"

Piece::Piece(bool color, unsigned value, char type) : color(color), value(value), hasMoved(false) {
  setType(type);
}

Piece::~Piece() {}

bool Piece::checkInBounds(unsigned col, unsigned row) { return (row < ROWS) && (col < COLS); }

bool Piece::getMoved() { return hasMoved; }
bool Piece::getColor() { return color; }
unsigned Piece::getValue() { return value; }
char Piece::getType() { return type; }

void Piece::setMoved(bool m) { hasMoved = m; }
inline void Piece::setType(char t) { type = (getColor() == 1) ? t : t + 32; }
