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

char Piece::colToChar() {
	const std::string cols = "abcdefgh";
	return cols[col - 1];
}



int Piece::getMatValue() {
	return matValue;
}

Color Piece::getPlayer() {
	return player;
}

void Piece::move(int r, int c) {
	row = r;
	col = c;
	moved = true;
}

std::string Piece::getName() {
	return name;
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

//debug functions

std::string Piece::pieceInfo() {
	std::string info = "";
	info += "Player: ";
	info += (player == 1 ? "White " : "Black ");
	info += "\nType: " + name + "\n";
	info += "MatValue: " + std::to_string(matValue) + "\n";
	info += "TileValue " + std::to_string(getTileValue(row, col)) + "\n";
	info += "Moved: " + std::to_string(moved) + "\n";
	info += "Tile: ";
	info += colToChar() + std::to_string(row);
	return info;
}