#include "pieces.hh"

Knight::Knight(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'N' : 'n';
	value = 320;
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