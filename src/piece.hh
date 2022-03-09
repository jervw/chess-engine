#pragma once
#include "move.hh"
#include <vector>
#include <memory>

class Board; // forward declaration

class Piece {

public:
	virtual ~Piece();
	virtual std::shared_ptr<Piece> clone() const = 0;

	virtual std::vector<Move> getMoves(Board*, unsigned, unsigned) = 0;

	int getSquareValue(unsigned, unsigned);
	bool getMoved();
	bool getColor();
	unsigned getValue();
	char getType();

	void setMoved(bool);
	void setType(char);

protected:
	Piece(bool, unsigned, char);
	const static unsigned ROWS = 8, COLS = 8;

	bool color;
	unsigned value;
	bool hasMoved;
	char type;

	bool checkInBounds(unsigned, unsigned);
};


