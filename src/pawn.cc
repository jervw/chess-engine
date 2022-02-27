#include "pieces.hh"

Pawn::Pawn(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'P' : 'p';
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