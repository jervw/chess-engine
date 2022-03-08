#pragma once
#include "piece.hh"
#include "board.hh"

// TODO, maybe inherit from rook and bishop?

class Queen : public Piece {

public:
	Queen(bool);
	std::shared_ptr<Piece> clone() const;
	std::vector<Move> getMoves(Board*, unsigned, unsigned);

private:
	const static unsigned MOVE_NUM = 8; // directions
	const static unsigned MIN_MOVE = 1; // least it may move
	const static unsigned MAX_MOVE = 8; // furthest it may move
};
