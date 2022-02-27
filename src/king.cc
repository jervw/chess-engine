#include "pieces.hh"
#include <iostream>
King::King(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'K' : 'k';
	board->addPiece(this);
}

bool King::possibleMove(int destRow, int destCol) {

	if (row == destRow && col == destCol)
		return false;

	if (abs(row - destRow) <= 1 && abs(col - destCol) <= 1)
		return true;

	return false;
}

bool King::legalMove(int destRow, int destCol, Board& board) {
	Piece* p = board.getPieceAt(destRow, destCol);
	if (p == NULL || p->getPlayer() != player)
		return true;
	return false;
}