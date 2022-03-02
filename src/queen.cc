#include "pieces.hh"

Queen::Queen(int row, int col, Color player, Board* board) : Piece(row, col, player, board) {
	symbol = player == 1 ? 'Q' : 'q';
	value = 900;
	board->addPiece(this);
}

bool Queen::possibleMove(int destRow, int destCol) {
	// check for same tile.
	if (row == destRow && col == destCol)
		return false;

	if (row == destRow || col == destCol)
		return true;

	if (abs(row - destRow) == abs(col - destCol))
		return true;


	return false;
}

bool Queen::legalMove(int destRow, int destCol, Board& board) {

	// Find the direction of the movement.
	int dirX = destCol - col > 0 ? 1 : (destCol - col == 0 ? 0 : -1);
	int dirY = destRow - row > 0 ? 1 : (destRow - row == 0 ? 0 : -1);

	int r = row + dirY;
	int c = col + dirX;

	while (1) {
		Piece* p = board.getPieceAt(r, c);

		if (p) {
			if (p->getPlayer() == player)
				return false;
			else {
				return r == destRow && c == destCol;
			}
		}

		if (r == destRow && c == destCol)
			return true;

		r += dirY;
		c += dirX;
	}
}