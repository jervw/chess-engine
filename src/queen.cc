#include "queen.hh"

Queen::Queen(bool color) : Piece(color, Params::QUEEN, 'Q') {}

std::shared_ptr<Piece> Queen::clone() const {
	return std::shared_ptr<Piece>(new Queen(*this));
}

std::vector<Move> Queen::getMoves(Board* board, unsigned col, unsigned row) {
	std::vector<Move> moveList;
	for (unsigned j = 0; j < MOVE_NUM; j++) {
		int x = col, y = row;
		for (unsigned i = MIN_MOVE; i < MAX_MOVE; i++, x = col, y = row) {
			switch (j) {
			case 0: y += i; break; // north
			case 1: x += i; y += i; break; // north-east
			case 2: x += i; break; // east
			case 3: x += i; y -= i; break; // south-east
			case 4: y -= i; break; // south
			case 5: x -= i; y -= i; break; // south-west
			case 6: x -= i; break; // west
			case 7: x -= i; y += i; break; // north-west
			}

			// check if valid move
			if (checkInBounds(x, y)) {
				Tile possibleMove = (*board)(x, y);
				if (possibleMove) { // check for own piece
					if (possibleMove.getPiece().getColor() != color)
						moveList.push_back(Move(col, row, x, y)); // capture
					break;
				}
				else  // not occupied
					moveList.push_back(Move(col, row, x, y));

			}
			// out of bounds
			else break;
		}
	}
	return moveList;
}