#pragma once
#include <sstream>

class Move {

public:
	Move();
	Move(unsigned, unsigned, unsigned, unsigned);

	std::string stateMove();

	unsigned getSrcCol();
	unsigned getSrcRow();
	unsigned getDestCol();
	unsigned getDestRow();

	std::pair <unsigned, unsigned> getSrc();
	std::pair <unsigned, unsigned> getDest();

	bool operator==(Move&);
	bool operator>=(Move&);
	bool operator<=(Move&);
	friend std::ostream& operator<<(std::ostream&, Move&);

private:
	unsigned srcCol, srcRow; // origin of move
	unsigned destCol, destRow; // destination of move
};
