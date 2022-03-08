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
	}
	return moveList;
}