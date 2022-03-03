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

char Tile::colToChar() const {
	const std::string cols = "abcdefgh";
	return cols[col - 1];
}

std::string Tile::toString() const {
	return colToChar() + std::to_string(row);
}