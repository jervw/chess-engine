#include "knight.hh"

Knight::Knight(bool color) : Piece(color, Params::KNIGHT, 'N') {}

std::shared_ptr<Piece> Knight::clone() const {
	return std::shared_ptr<Piece>(new Knight(*this));
}

std::vector<Move> Knight::getMoves(Board* board, unsigned col, unsigned row) {
	std::vector<Move> moveList;
	for (unsigned i = 0; i < MOVE_NUM; i++) {
		int x = col, y = row;

		switch (i) {
		case 0: x += MIN_MOVE; y += MAX_MOVE; break;
		case 1: x -= MIN_MOVE; y += MAX_MOVE; break;
		case 2: x += MAX_MOVE; y += MIN_MOVE; break;
		case 3: x += MAX_MOVE; y -= MIN_MOVE; break;
		case 4: x -= MAX_MOVE; y += MIN_MOVE; break;
		case 5: x -= MAX_MOVE; y -= MIN_MOVE; break;
		case 6: x += MIN_MOVE; y -= MAX_MOVE; break;
		case 7: x -= MIN_MOVE; y -= MAX_MOVE; break;
		}

		// check if valid move
		if (checkInBounds(x, y)) {
			Tile possibleMove = (*board)(x, y);
			if (possibleMove) { // check for own piece
				if (possibleMove.getPiece().getColor() != color)
					moveList.push_back(Move(col, row, x, y)); // capture
			}
			else // not occupied
				moveList.push_back(Move(col, row, x, y));

		}
	}
	return moveList;
}