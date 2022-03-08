#pragma once
#include "piece.hh"
#include "board.hh"

class Pawn : public Piece {

public:
	Pawn(bool);
	std::shared_ptr<Piece> clone() const;
	std::vector<Move> getMoves(Board*, unsigned, unsigned);

private:
	const static unsigned MOVE_NUM = 4; // directions
	const static unsigned MIN_MOVE = 1; // least it may move
	const static unsigned MAX_MOVE = 2; // furthest it may move
	const static bool WHITE = true, BLACK = false;
};
