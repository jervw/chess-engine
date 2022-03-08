#pragma once
#include "piece.hh"
#include "board.hh"

class Knight : public Piece {
public:
	Knight(bool);
	std::shared_ptr<Piece> clone() const;
	std::vector<Move> getMoves(Board*, unsigned, unsigned);
private:
	const static unsigned MOVE_NUM = 8; // directions
	const static unsigned MIN_MOVE = 1; // minimum move distance
	const static unsigned MAX_MOVE = 2; // maximum move distance
};
