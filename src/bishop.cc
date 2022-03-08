#include "bishop.hh"

Bishop::Bishop(bool color) : Piece(color, Params::BISHOP, 'B') {}

std::shared_ptr<Piece> Bishop::clone() const {
	return std::shared_ptr<Piece>(new Bishop(*this));
}

std::vector<Move> Bishop::getMoves(Board* board, unsigned col, unsigned row) {
	std::vector<Move> moveList;
	for (unsigned j = 0; j < MOVE_NUM; j++) {
		int x = col, y = row;

		for (unsigned i = MIN_MOVE; i < MAX_MOVE; i++, x = col, y = row) {
			switch (j) {
			case 0: x += i; y += i; break; // north-east
			case 1: x += i; y -= i; break; // south-east
			case 2: x -= i; y -= i; break; // south-west
			case 3: x -= i; y += i; break; // north-west
			}

			// check if valid move
			if (checkInBounds(x, y)) {
				Tile possibleMove = (*board)(x, y);
				if (possibleMove) { // check for own piece
					if (possibleMove.getPiece().getColor() != color)
						moveList.push_back(Move(col, row, x, y)); // capture

					break;
				}
				else // not occupied
					moveList.push_back(Move(col, row, x, y));

			}
			// out of bounds
			else break;
		}
	}
	return moveList;
}