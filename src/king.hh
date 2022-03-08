#pragma once
#include "piece.hh"
#include "board.hh"

class King : public Piece {

public:
	King(bool);
	std::shared_ptr<Piece> clone() const;
	std::vector<Move> getMoves(Board*, unsigned, unsigned);
private:
	const static unsigned MOVE_NUM = 8; // directions
	const static unsigned MIN_MOVE = 1; // minimum move distance
	const static unsigned MAX_MOVE = 1; // maximum move distance
	const static unsigned CASTLE_MOVE = 2; // castling

	void removeSurroundingKings(Board*, std::vector<Move>&);
	void removeCheckedMoves(Board*, std::vector<Move>&);
};
