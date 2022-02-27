#include "tile.hh"

Tile::Tile() {
	row = col = 0;
}

Tile::Tile(int r, int c) : row(r), col(c) {}

bool Tile::operator==(const Tile& other) const {
	return row == other.row && col == other.col;
}

int Tile::getRow() const {
	return row;
}

int Tile::getCol() const {
	return col;
}