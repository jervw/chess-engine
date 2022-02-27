#pragma once

#include "pieces.hh"

class Piece;

class Move {
private:
	Piece* movedPiece;
	Piece* attackedPiece;
	Piece* promotedPiece; // Set only for promotion moves.
	int srcRow, srcCol, dstRow, dstCol;
	bool pieceHadMoved;

public:
	Move(Piece*, Piece*, Piece*, int, int, int, int);
	Piece* getMovedPiece();
	Piece* getAttackedPiece();
	Piece* getPromotedPiece();
	int getSrcRow();
	int getSrcCol();
	int getDstRow();
	int getDstCol();
	bool getPieceHadMoved();
};
