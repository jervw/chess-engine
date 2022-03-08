#include "rook.hh"

Rook::Rook(bool color) : Piece(color, Params::ROOK, 'R') {}

std::shared_ptr<Piece> Rook::clone() const {
	return std::shared_ptr<Piece>(new Rook(*this));
}

std::vector<Move> Rook::getMoves(Board* board, unsigned col, unsigned row) {
	std::vector<Move> moveList;
	for (unsigned j = 0; j < MOVE_NUM; j++) {
		int x = col, y = row;
		for (unsigned i = MIN_MOVE; i < MAX_MOVE; i++, x = col, y = row) {
			switch (j) {
			case 0: y += i; break; // north
			case 1: x += i; break; // east
			case 2: y -= i; break; // south
			case 3: x -= i; break; // west
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