#include "pawn.hh"

Pawn::Pawn(bool color) : Piece(color, Params::PAWN, 'P') {}

std::shared_ptr<Piece> Pawn::clone() const {
	return std::shared_ptr<Piece>(new Pawn(*this));
}

std::vector<Move> Pawn::getMoves(Board* board, unsigned col, unsigned row) {
	std::vector<Move> moveList;

	// white moves north, black moves south
	int offset = (getColor() == WHITE) ? 1 : -1;

	for (unsigned i = 0; i < MOVE_NUM; i++) {
		if (i == 1 && getMoved()) continue;

		int x = col, y = row;
		switch (i) {
		case 0: y += (MIN_MOVE * offset); break; // one forward
		case 1: y += (MAX_MOVE * offset); break; // two forward
		case 2: y += (MIN_MOVE * offset); x += MIN_MOVE; break; // right digonal
		case 3: y += (MIN_MOVE * offset); x -= MIN_MOVE; break; // left diagonal
		}

		// check if valid move
		if (checkInBounds(x, y)) {
			// cannot capture going forward
			if ((i == 0 || i == 1) && (*board)(x, y)) continue;
			// cannot jump over pieces
			if (i == 1 && (*board)(x, y - (MIN_MOVE * offset))) continue;

			Tile possibleMove = (*board)(x, y);
			if ((i == 2 || i == 3) && possibleMove) {
				// check for colror
				if (possibleMove.getPiece().getColor() != color)
					moveList.push_back(Move(col, row, x, y)); // capture

			}
			else if (!(i == 2 || i == 3)) // not occupied
				moveList.push_back(Move(col, row, x, y));
		}

		// En Passant
		if (i == 1 && !getMoved() && !(*board)(col, row)) {
			// check if there is a pawn to the left
			if (col > 0 && (*board)(col - 1, row)) {
				if ((*board)(col - 1, row).getPiece().getValue() == Params::PAWN) {
					if ((*board)(col - 1, row).getPiece().getColor() != color)
						moveList.push_back(Move(col, row, col - 1, row)); // capture
				}
			}
			// check if there is a pawn to the right
			if (col < BOARD_S - 1 && (*board)(col + 1, row)) {
				if ((*board)(col + 1, row).getPiece().getValue() == Params::PAWN) {
					if ((*board)(col + 1, row).getPiece().getColor() != color)
						moveList.push_back(Move(col, row, col + 1, row)); // capture
				}
			}

		}
	}
	return moveList;
}