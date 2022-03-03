#include "pieces.hh"

Knight::Knight(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'N' : 'n';
	name = "Knight";
	matValue = 320;
	board->addPiece(this);
}

bool Knight::possibleMove(int destRow, int destCol) {

	if (abs(row - destRow) == 2 && abs(col - destCol) == 1)
		return true;

	if (abs(row - destRow) == 1 && abs(col - destCol) == 2)
		return true;


	return false;
}

bool Knight::legalMove(int destRow, int destCol, Board& board) {
	Piece* p = board.getPieceAt(destRow, destCol);
	if (p == NULL || p->getPlayer() != player)
		return true;
	return false;
}

int Knight::getTileValue(int row, int col) {
	const int TILE_VALUES[8][8] = {
	{-50,-40,-30,-30,-30,-30,-40,-50},
	{-40,-20,  0,  0,  0,  0,-20,-40},
	{-30,  0, 10, 15, 15, 10,  0,-30},
	{-30,  5, 15, 20, 20, 15,  5,-30},
	{-30,  0, 15, 20, 20, 15,  0,-30},
	{-30,  5, 10, 15, 15, 10,  5,-30},
	{-40,-20,  0,  5,  5,  0,-20,-40},
	{-50,-40,-30,-30,-30,-30,-40,-50} };

	return TILE_VALUES[row - 1][col - 1];
}
