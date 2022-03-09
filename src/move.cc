#include "move.hh"

Move::Move() {}

Move::Move(unsigned sC, unsigned sR, unsigned dC, unsigned dR) : srcCol(sC), srcRow(sR), destCol(dC), destRow(dR) {}

std::string Move::stateMove() {
	std::stringstream s;
	s << (char)(srcCol + 97) << (char)(srcRow + 49); // origin
	s << (char)(destCol + 97) << (char)(destRow + 49); // destination
	s << std::endl;
	return s.str();
}

unsigned Move::getSrcCol() { return srcCol; }
unsigned Move::getSrcRow() { return srcRow; }
unsigned Move::getDestCol() { return destCol; }
unsigned Move::getDestRow() { return destRow; }

bool Move::operator==(Move& m) {
	bool sameOrig = (getSrcCol() == m.getSrcCol() && getSrcRow() == m.getSrcRow());
	bool sameDest = (getDestCol() == m.getDestCol() && getDestRow() == m.getDestRow());
	return sameOrig && sameDest;
}

bool Move::operator<=(Move& m) {
	return (getSrcCol() == m.getSrcCol() && getSrcRow() == m.getSrcRow());
}

bool Move::operator>=(Move& m) {
	return (getDestCol() == m.getDestCol() && getDestRow() == m.getDestRow());
}


std::ostream& operator<<(std::ostream& out, Move& m) {
	out << m.stateMove();
	return out;
}