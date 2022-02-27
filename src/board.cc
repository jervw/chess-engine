#include <algorithm>
#include <iostream>
#include "board.hh"
#include "game.hh"
#include "pieces.hh"


Board::Board() {
	currentMove = 0;
	pieces = new Piece * [64];
	for (int i = 0; i < 64; i++)
		pieces[i] = NULL;

	initBoard();
}

Board::~Board() {

	while (currentMove < preMoves.size())
		goForward();

	// deallocate current pieces
	for (int i = 0; i < 64; i++) {
		if (pieces[i] != NULL)
			delete pieces[i];
	}
	delete[] pieces;

	// dellocate pieces which are not in the board
	std::vector<Move>::iterator it;
	for (it = preMoves.begin(); it != preMoves.end(); it++) {

		// deallocate destroyed pieces.
		if (it->getAttackedPiece() != NULL)
			delete it->getAttackedPiece();

		// deallocate promoted pawns.
		if (it->getPromotedPiece() != NULL)
			delete it->getMovedPiece();
	}
}

void Board::initBoard() {

	// White.
	Rook* r1 = new Rook(1, 1, WHITE, this);
	Knight* n1 = new Knight(1, 2, WHITE, this);
	Bishop* b1 = new Bishop(1, 3, WHITE, this);
	Queen* q = new Queen(1, 5, WHITE, this);
	Bishop* b2 = new Bishop(1, 6, WHITE, this);
	Knight* n2 = new Knight(1, 7, WHITE, this);
	King* k = new King(1, 4, WHITE, this);
	Rook* r2 = new Rook(1, 8, WHITE, this);
	Pawn* p1 = new Pawn(2, 1, WHITE, this);
	Pawn* p2 = new Pawn(2, 2, WHITE, this);
	Pawn* p3 = new Pawn(2, 3, WHITE, this);
	Pawn* p4 = new Pawn(2, 4, WHITE, this);
	Pawn* p5 = new Pawn(2, 5, WHITE, this);
	Pawn* p6 = new Pawn(2, 6, WHITE, this);
	Pawn* p7 = new Pawn(2, 7, WHITE, this);
	Pawn* p8 = new Pawn(2, 8, WHITE, this);

	// Black.
	Rook* R1 = new Rook(8, 1, BLACK, this);
	Knight* N1 = new Knight(8, 2, BLACK, this);
	Bishop* B1 = new Bishop(8, 3, BLACK, this);
	King* K = new King(8, 4, BLACK, this);
	Queen* Q = new Queen(8, 5, BLACK, this);
	Bishop* B2 = new Bishop(8, 6, BLACK, this);
	Knight* N2 = new Knight(8, 7, BLACK, this);
	Rook* R2 = new Rook(8, 8, BLACK, this);
	Pawn* P1 = new Pawn(7, 1, BLACK, this);
	Pawn* P2 = new Pawn(7, 2, BLACK, this);
	Pawn* P3 = new Pawn(7, 3, BLACK, this);
	Pawn* P4 = new Pawn(7, 4, BLACK, this);
	Pawn* P5 = new Pawn(7, 5, BLACK, this);
	Pawn* P6 = new Pawn(7, 6, BLACK, this);
	Pawn* P7 = new Pawn(7, 7, BLACK, this);
	Pawn* P8 = new Pawn(7, 8, BLACK, this);

}

void Board::addPiece(Piece* piece) {

	// if piece is king save it
	if (piece->getSymbol() == 'k')
		bKing = piece;
	else if (piece->getSymbol() == 'K')
		wKing = piece;

	// add the piece to the array.
	int index = convertToIndex(piece->getRow(), piece->getCol());

	if (pieces[index] != NULL)
		delete pieces[index];
	pieces[index] = piece;
}

bool Board::movePiece(int srcRow, int srcCol, int dstRow, int dstCol) {
	int srcIndex = convertToIndex(srcRow, srcCol);
	int dstIndex = convertToIndex(dstRow, dstCol);

	Piece* srcP = pieces[srcIndex];
	Piece* dstP = pieces[dstIndex];

	if (srcP != NULL) {

		// check for pawn promotion
		bool promoteMove = false;
		if (dynamic_cast<Pawn*> (srcP)) {
			if (dstRow == 8 && srcP->getPlayer() == 1) {
				promoteMove = true;
			}
			else if (dstRow == 1 && srcP->getPlayer() == 2) {
				promoteMove = true;
			}
		}

		// create the new queen if necessary.
		Queen* q = NULL;
		if (promoteMove)
			q = new Queen(dstRow, dstCol, srcP->getPlayer(), this);

		// create the new move.
		Move mData(srcP, dstP, q, srcRow, srcCol, dstRow, dstCol);
		preMoves.push_back(mData);

		if (!q) {
			srcP->move(dstRow, dstCol);
			pieces[dstIndex] = srcP;
		}
		else
			pieces[dstIndex] = q;
		pieces[srcIndex] = NULL;
		currentMove++;

		// revert if the king is not safe.
		if (!isKingSafe(srcP->getPlayer())) {
			revertLastMove();
			return false;
		}
		return true;
	}
	return false;
}


void Board::revertLastMove() {
	if (preMoves.size() > 0) {
		Move move = preMoves[preMoves.size() - 1];

		int srcIndex = convertToIndex(move.getSrcRow(), move.getSrcCol());
		int dstIndex = convertToIndex(move.getDstRow(), move.getDstCol());

		move.getMovedPiece()->move(move.getSrcRow(), move.getSrcCol());
		move.getMovedPiece()->setMoved(move.getPieceHadMoved());

		pieces[srcIndex] = move.getMovedPiece();
		pieces[dstIndex] = move.getAttackedPiece();

		currentMove--;

		preMoves.pop_back();
	}
}

// go back to view previous moves
void Board::goBack() {
	if (currentMove > 0) {
		Move mData = preMoves[currentMove - 1];

		int srcIndex = convertToIndex(mData.getSrcRow(), mData.getSrcCol());
		int dstIndex = convertToIndex(mData.getDstRow(), mData.getDstCol());

		mData.getMovedPiece()->move(mData.getSrcRow(), mData.getSrcCol());
		mData.getMovedPiece()->setMoved(mData.getPieceHadMoved());

		pieces[srcIndex] = mData.getMovedPiece();
		pieces[dstIndex] = mData.getAttackedPiece();

		currentMove--;
	}
}

// go forward to view previous moves
void Board::goForward() {
	if (currentMove < preMoves.size()) {
		Move mData = preMoves[currentMove];

		int srcIndex = convertToIndex(mData.getSrcRow(), mData.getSrcCol());
		int dstIndex = convertToIndex(mData.getDstRow(), mData.getDstCol());

		Piece* srcP = pieces[srcIndex];

		srcP->move(mData.getDstRow(), mData.getDstCol());
		if (mData.getPromotedPiece() == NULL)
			pieces[dstIndex] = srcP;
		else
			pieces[dstIndex] = mData.getPromotedPiece();
		pieces[srcIndex] = NULL;

		currentMove++;
	}
}

bool Board::isAttacked(int row, int col, int byPlayer) {
	for (int i = 0; i < 64; i++) {
		Piece* p = pieces[i];
		if (p == NULL)
			continue;

		if (p->getPlayer() == byPlayer) {
			Pawn* pawn = dynamic_cast<Pawn*>(p);
			if (pawn) {
				if (pawn->checkAttack(row, col))
					return true;
			}
			else if (p->possibleMove(row, col) && p->legalMove(row, col, *this))
				return true;
		}
	}
	return false;
}

bool Board::isKingSafe(int which) {
	if (which == 1)
		return !isAttacked(wKing->getRow(), wKing->getCol(), 2);
	return !isAttacked(bKing->getRow(), bKing->getCol(), 1);
}

bool Board::movesLeft(int player) {

	for (int i = 0; i < 64; i++) {
		Piece* p = pieces[i];
		if (p == NULL || p->getPlayer() != player)
			continue;

		std::vector<Tile> availMoves = p->getPossibleTiles(*this);
		std::vector<Tile>::iterator it;


		for (it = availMoves.begin(); it != availMoves.end(); it++) {
			bool success = movePiece(p->getRow(), p->getCol(), it->getRow(), it->getCol());

			// If the move was successful, revert it and return true.
			if (success) {
				revertLastMove();
				return true;
			}
		}
	}

	return false; // no possible moves
}

int Board::convertToIndex(int row, int col) {
	return (row - 1) * 8 + (col - 1);
}


std::vector<Piece*> Board::getPieces(int player) {
	std::vector<Piece*> playerPieces;
	for (int i = 0; i < 64; i++) {
		Piece* p = pieces[i];
		if (p != NULL && p->getPlayer() == player)
			playerPieces.push_back(p);
	}
	return playerPieces;
}


Piece* Board::getPieceAt(int row, int col) {
	if (row < 1 || row > 8 || col < 1 || col > 8)
		return NULL;
	return pieces[convertToIndex(row, col)];
}


void Board::printBoard(int selectedRow, int selectedCol, const std::vector<Tile>& highlighted) {

	// tile size
	const int TILE_SIZE_X = 6;
	const int TILE_SIZE_Y = 3;

	// color codes.
	const std::string WHITE = "\033[30;47m";
	const std::string BLACK = "\033[37;40m";
	const std::string BLUE = "\033[37;44m";
	const std::string GREEN = "\033[37;42m";
	const std::string DEFAULT = "\033[0m";

	std::cout << "       a     b     c     d     e     f     g     h\n\n";

	for (int j = 1; j <= TILE_SIZE_Y * 8; j++) {
		for (int i = 0; i <= TILE_SIZE_X * 8; i++) {

			// oordinates of the current tile
			int tileRow = 9 - ((j - 1) / TILE_SIZE_Y + 1);
			int tileCol = i == 0 ? -1 : (i - 1) / TILE_SIZE_X + 1;

			if (i == 0) {
				if ((j - 2) % 3 == 0)
					std::cout << 8 - (j - 2) / 3 << "   ";
				else
					std::cout << "    ";
			}
			else {
				// select color.
				if (tileCol == selectedCol && tileRow == selectedRow)
					std::cout << BLUE;
				else if (find(highlighted.begin(), highlighted.end(), Tile(tileRow, tileCol)) != highlighted.end())
					std::cout << GREEN;

				else {
					if (tileCol % 2 == tileRow % 2)
						std::cout << WHITE;
					else
						std::cout << BLACK;
				}

				// draw
				if ((i - 10) % TILE_SIZE_X == 0 && (j - 2) % TILE_SIZE_Y == 0) {
					Piece* p = getPieceAt(tileRow, tileCol);

					if (p)
						std::cout << p->getSymbol();
					else
						std::cout << " ";
				}
				else
					std::cout << " ";

				// restore color.
				std::cout << DEFAULT;

				// add the numbers at the end.
				if (i == TILE_SIZE_X * 8 && (j - 2) % 3 == 0)
					std::cout << "   " << 8 - (j - 2) / 3;
			}
		}
		std::cout << std::endl;
	}

	std::cout << "\n       a     b     c     d     e     f     g     h\n";
}

// clear the board, comment out for debugging.
void Board::clear() {
	std::cout << "\033c";
}
