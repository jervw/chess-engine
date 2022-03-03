#include "pieces.hh"

Pawn::Pawn(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'P' : 'p';
	name = "Pawn";
	matValue = 100;
	board->addPiece(this);
}

bool Pawn::possibleMove(int destRow, int destCol) {
	// movement direction
	int sign = player == 1 ? 1 : -1;

	if (col == destCol) {
		if (moved) {
			if (destRow == row + 1 * sign)
				return true;
		}
		else {
			if (destRow == row + 1 * sign || destRow == row + 2 * sign)
				return true;
		}
	}
	else if (abs(col - destCol) == 1) {
		if (destRow == row + 1 * sign)
			return true;
	}
	return false;
}

bool Pawn::legalMove(int destRow, int destCol, Board& board) {

	if (col == destCol) {
		if (player == 1) {
			for (int i = row + 1; i <= destRow; i++) {
				if (board.getPieceAt(i, col) != NULL)
					return false;
			}
		}
		else {
			for (int i = row - 1; i >= destRow; i--) {
				if (board.getPieceAt(i, col) != NULL)
					return false;
			}
		}
		return true;
	}
	else {
		Piece* p = board.getPieceAt(destRow, destCol);
		if (p != NULL && p->getPlayer() != player)
			return true;
		else
			return false;
	}
}

bool Pawn::checkAttack(int r, int c) {
	int dir = player == 1 ? 1 : -1;
	if (r == row + dir && abs(c - col) == 1)
		return true;
	return false;
}

int Pawn::getTileValue(int row, int col) {
	const int TILE_VALUES[8][8] = {
	{ 0,  0,  0,  0,  0,  0,  0,  0 },
	{ 50, 50, 50, 50, 50, 50, 50, 50 },
	{ 10, 10, 20, 30, 30, 20, 10, 10 },
	{  5,  5, 10, 25, 25, 10,  5,  5 },
	{  0,  0,  0, 20, 20,  0,  0,  0 },
	{  5, -5,-10,  0,  0,-10, -5,  5 },
	{  5, 10, 10,-20,-20, 10, 10,  5 },
	{  0,  0,  0,  0,  0,  0,  0,  0 } };

	return TILE_VALUES[row - 1][col - 1];
}

