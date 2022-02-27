#include "pieces.hh"
#include <iostream>
Piece::Piece(int row, int col, Color player, Board* board) : row(row), col(col), player(player), board(board) {
	moved = false;
}

std::vector<Tile> Piece::getPossibleTiles(Board& board) {

	std::vector<Tile> tiles;
	for (int r = 1; r <= 8; r++) {
		for (int c = 1; c <= 8; c++) {
			if (possibleMove(r, c) && legalMove(r, c, board)) {
				tiles.push_back(Tile(r, c));
			}
		}
	}
	return tiles;
}

int Piece::getRow() {
	return row;
}

int Piece::getCol() {
	return col;
}

Color Piece::getPlayer() {
	return player;
}

void Piece::move(int r, int c) {
	row = r;
	col = c;
	moved = true;
}

char Piece::getSymbol() {
	return symbol;
}

bool Piece::getMoved() {
	return moved;
}

void Piece::setMoved(bool moved) {
	this->moved = moved;
}