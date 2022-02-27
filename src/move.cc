#include "move.hh"
#include <iostream>

Move::Move(Piece* mvPiece, Piece* attPiece, Piece* promPiece, int sRow, int sCol, int dRow, int dCol) {

	movedPiece = mvPiece;
	attackedPiece = attPiece;
	promotedPiece = promPiece;
	srcRow = sRow;
	srcCol = sCol;
	dstRow = dRow;
	dstCol = dCol;
	pieceHadMoved = movedPiece->getMoved();
}

Piece* Move::getMovedPiece() {
	return movedPiece;
}

Piece* Move::getAttackedPiece() {
	return attackedPiece;
}

Piece* Move::getPromotedPiece() {
	return promotedPiece;
}

int Move::getSrcRow() {
	return srcRow;
}

int Move::getSrcCol() {
	return srcCol;
}

int Move::getDstRow() {
	return dstRow;
}

int Move::getDstCol() {
	return dstCol;
}

bool Move::getPieceHadMoved() {
	return pieceHadMoved;
}