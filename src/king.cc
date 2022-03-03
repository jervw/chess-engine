#include "pieces.hh"
#include <iostream>
King::King(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'K' : 'k';
	name = "King";
	matValue = 20000;
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

int King::getTileValue(int row, int col) {
	const int TILE_VALUES[8][8] = {
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-20,-30,-30,-40,-40,-30,-30,-20},
	{-10,-20,-20,-20,-20,-20,-20,-10},
	{ 20, 20,  0,  0,  0,  0, 20, 20},
	{ 20, 30, 10,  0,  0, 10, 30, 20 } };

	return TILE_VALUES[row - 1][col - 1];
}