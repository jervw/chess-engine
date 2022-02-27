#pragma once

class Tile {

public:
	Tile();
	Tile(int, int);
	bool operator==(const Tile&) const;

	int getRow() const;
	int getCol() const;

private:
	int row, col;
};
