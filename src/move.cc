#include "move.hh"

Move::Move() {}

Move::Move(int sC, int sR, int dC, int dR) : srcCol(sC), srcRow(sR), destCol(dC), destRow(dR) {}

int Move::getSrcCol() { return srcCol; }
int Move::getSrcRow() { return srcRow; }
int Move::getDestCol() { return destCol; }
int Move::getDestRow() { return destRow; }

std::string Move::moveToString() {
	std::stringstream toReturn;
	toReturn << (char)(srcCol + 97) << (char)(srcRow + 49); // origin
	toReturn << (char)(destCol + 97) << (char)(destRow + 49); // destination
	return toReturn.str();
}

std::ostream& operator<<(std::ostream& out, Move& m) {
	out << m.moveToString();
	return out;
}