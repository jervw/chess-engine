#pragma once
#include <iostream>
#include "piece.hh"

class Tile {

public:
	Tile();
	Tile(Piece* p);
	Tile(const Tile& t);
	~Tile();

	void reset();
	Piece& getPiece();

	Tile& operator=(const Tile&);
	Tile& operator=(Piece*);
	operator bool() const;
	friend std::ostream& operator<<(std::ostream&, Tile&);

private:
	std::shared_ptr<Piece> occupant; // occupying piece
};
