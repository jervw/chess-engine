#pragma once
#include "piece.hh"
#include "board.hh"

class Rook : public Piece {

public:
	Rook(bool);
	std::shared_ptr<Piece> clone() const;
	std::vector<Move> getMoves(Board*, unsigned, unsigned);

private:
	const static unsigned MOVE_NUM = 4; // directions
	const static unsigned MIN_MOVE = 1; // least it may move
	const static unsigned MAX_MOVE = 8; // furthest it may move
};
