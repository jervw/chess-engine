#include "king.hh"

King::King(bool color) : Piece(color, Params::KING, 'K') {}

std::shared_ptr<Piece> King::clone() const {
	return std::shared_ptr<Piece>(new King(*this));
}


std::vector<Move> King::getMoves(Board* board, unsigned col, unsigned row) {
	std::vector<Move> moveList;
	for (unsigned j = 0; j < MOVE_NUM; j++) {
		int x = col, y = row;

		switch (j) {
		case 0: y += MIN_MOVE; break; // north
		case 1: x += MIN_MOVE; y += MIN_MOVE; break; // north-east
		case 2: x += MIN_MOVE; break; // east
		case 3: x += MIN_MOVE; y -= MIN_MOVE; break; // south-east
		case 4: y -= MIN_MOVE; break; // south
		case 5: x -= MIN_MOVE; y -= MIN_MOVE; break; // south-west
		case 6: x -= MIN_MOVE; break; // west
		case 7: x -= MIN_MOVE; y += MIN_MOVE; break; // north-west
		}

		// check if valid move
		if (checkInBounds(x, y)) {
			Tile possibleMove = (*board)(x, y);
			if (possibleMove) {
				if (possibleMove.getPiece().getColor() != color)
					moveList.push_back(Move(col, row, x, y)); // capture

			}
			else // not occupied
				moveList.push_back(Move(col, row, x, y));

		}
	}

	// check for castling
	bool checkWhitePos = (getColor() && col == 4 && row == 0); // valid white king position
	bool checkBlackPos = (!getColor() && col == 4 && row == 7); // valid black king position

	if (!getMoved() && (checkWhitePos || checkBlackPos)) { // if first move
		for (unsigned j = 0; j < CASTLE_MOVE; j++)
			for (unsigned i = 1; i < ((j == 0) ? 4 : 5); ++i) {
				Tile castle = (*board)(((j == 0) ? col + i : col - i), row);

				if (!castle) continue; // continue as not edge tile
				else if (i < ((j == 0) ? 3 : 4)) break; // if occupied 

				// check for own piece
				if (castle.getPiece().getColor() == getColor())
					if (castle.getPiece().getValue() == Params::ROOK)
						if (!castle.getPiece().getMoved()) {
							// if same color, valid castle
							Move castleMove(col, row, (j == 0) ? col + i : col - i, row);
							moveList.push_back(castleMove);
						}
			}
	}

	// remove invalid moves
	removeSurroundingKings(board, moveList);
	removeCheckedMoves(board, moveList);
	return moveList;
}

// method to remove moves which put king next to king
inline void King::removeSurroundingKings(Board* board, std::vector<Move>& moveList) {
	std::vector<int> indexes;
	for (unsigned j = 0; j < moveList.size(); j++) {
		for (unsigned i = 0; i < MOVE_NUM; i++) {
			int x = moveList[j].getDestCol(), y = moveList[j].getDestRow();
			switch (i) {
			case 0: y += MIN_MOVE; break; // north
			case 1: x += MIN_MOVE; y += MIN_MOVE; break; // north-east
			case 2: x += MIN_MOVE; break; // east
			case 3: x += MIN_MOVE; y -= MIN_MOVE; break; // south-east
			case 4: y -= MIN_MOVE; break; // south
			case 5: x -= MIN_MOVE; y -= MIN_MOVE; break; // south-west
			case 6: x -= MIN_MOVE; break; // west
			case 7: x -= MIN_MOVE; y += MIN_MOVE; break; // north-west
			}

			// check if move is in bounds and has a piece
			if (checkInBounds(x, y) && (*board)(x, y))
				if ((*board)(x, y).getPiece().getColor() != getColor())
					if ((*board)(x, y).getPiece().getValue() == Params::KING)
						indexes.insert(indexes.begin(), j);
		}
	}
	for (unsigned i = 0; i < indexes.size(); i++) {
		moveList.erase(moveList.begin() + indexes[i]);
	}
	indexes.clear();
}

// remove moves which would put king in check
inline void King::removeCheckedMoves(Board* board, std::vector<Move>& moveList) {
	std::vector<int> indexes;

	for (unsigned i = 0; i < moveList.size(); i++) {
		// make move on a copy and check if in check
		Board* copy = new Board(*board);
		copy->movePiece(moveList[i]);
		if (copy->determineCheck(getColor()))
			indexes.insert(indexes.begin(), i);
		delete copy; // free memory
	}
	for (unsigned i = 0; i < indexes.size(); i++)
		moveList.erase(moveList.begin() + indexes[i]);

	indexes.clear();
}
