#pragma once
#include <string>

class Tile {

public:
	Tile();
	Tile(int, int);
	bool operator==(const Tile&) const;

	int getRow() const;
	int getCol() const;
	char colToChar() const;
	std::string toString() const;

private:
	int row, col;
};
