#pragma once
#include "tile.hh"
#include "params.hh"
#include "knight.hh"
#include "bishop.hh"
#include "rook.hh"
#include "queen.hh"
#include "king.hh"
#include "pawn.hh"
#include <fstream>
#include <algorithm>

#define BOARD_S 8

enum Column { A, B, C, D, E, F, G, H };

class Board {

public:
	Board();

	void printBoard(int = -1, int = -1, std::vector<Move> = std::vector<Move>());
	void movePiece(Move);

	// operator overloads for easy tile access
	Tile& operator()(int, int);
	Tile const& operator()(int, int) const;

private:
	Tile tiles[BOARD_S][BOARD_S];
	const static bool WHITE = true, BLACK = false;

	std::vector<Move> getAllNonKingMoves(bool);
};
