#pragma once

#include <vector>
#include "pieces.hh"
#include "move.hh"
#include "tile.hh"

class Piece;
class Move;

class Board {
public:
	Board();
	~Board();

	std::vector<Piece*> getPieces(int player);
	Piece* getPieceAt(int, int);

	void addPiece(Piece*);
	bool movePiece(int, int, int, int);
	bool movesLeft(int);
	bool isKingSafe(int);
	void goBack();
	void goForward();
	void revertLastMove();
	void initBoard();
	void printBoard(int, int, const std::vector<Tile>&);
	void clear();

private:
	Piece** pieces; // 64 pieces
	Piece* wKing, * bKing; // save pointers to kings
	std::vector<Move> preMoves; // previous moves
	int currentMove; // current move

	bool isAttacked(int, int, int);
	int convertToIndex(int, int);
};

