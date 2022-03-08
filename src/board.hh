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

	std::vector<Piece*> getPieces(int player = 0) const;
	Piece* getPieceAt(int, int);

	void addPiece(Piece*);
	bool movePiece(int, int, int, int);
	bool movesLeft(int);
	bool isKingSafe(int);
	void goBack();
	void goForward();
	void undoMove();
	void initBoard();
	void printBoard();
	void clear();

private:
	Piece** pieces; // 64 pieces
	Piece* wKing, * bKing; // save pointers to kings
	std::vector<Move> movesMade; // previous moves
	int currentMove; // current move

	bool isAttacked(int, int, int);
	int convertToIndex(int, int);
};

