#pragma once
#include <sstream>

class Move {
public:
	Move();
	Move(int, int, int, int);

	int getSrcRow();
	int getSrcCol();
	int getDestCol();
	int getDestRow();

	std::string moveToString();

	bool operator==(Move&);
	bool operator>=(Move&);
	bool operator<=(Move&);
	friend std::ostream& operator<<(std::ostream&, Move&);

private:
	int srcCol, srcRow;
	int destCol, destRow;
};
