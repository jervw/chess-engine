#include "board.hh"

Board::Board() {
	// black
	(*this)(A, 7) = new Rook(BLACK);
	(*this)(B, 7) = new Knight(BLACK);
	(*this)(C, 7) = new Bishop(BLACK);
	(*this)(D, 7) = new Queen(BLACK);
	(*this)(E, 7) = new King(BLACK);
	(*this)(F, 7) = new Bishop(BLACK);
	(*this)(G, 7) = new Knight(BLACK);
	(*this)(H, 7) = new Rook(BLACK);

	for (unsigned i = 0; i < BOARD_S; i++)
		(*this)(i, 6) = new Pawn(BLACK);

	// white
	(*this)(A, 0) = new Rook(WHITE);
	(*this)(B, 0) = new Knight(WHITE);
	(*this)(C, 0) = new Bishop(WHITE);
	(*this)(D, 0) = new Queen(WHITE);
	(*this)(E, 0) = new King(WHITE);
	(*this)(F, 0) = new Bishop(WHITE);
	(*this)(G, 0) = new Knight(WHITE);
	(*this)(H, 0) = new Rook(WHITE);

	for (unsigned i = 0; i < BOARD_S; i++)
		(*this)(i, 1) = new Pawn(WHITE);
}

void Board::movePiece(Move m) {
	bool color = (*this)(m.getSrcCol(), m.getSrcRow()).getPiece().getColor();
	Tile destMove = (*this)(m.getDestCol(), m.getDestRow());
	if (destMove && destMove.getPiece().getColor() != color)
		(*this)(m.getDestCol(), m.getDestRow()).reset();

	// make copy of original tile
	switch ((*this)(m.getSrcCol(), m.getSrcRow()).getPiece().getType()) {
	case 'P': case 'p': // pawn
		// promotes to queen if at end of board
		if (m.getDestRow() == BOARD_S - 1 && color == WHITE)
			(*this)(m.getDestCol(), m.getDestRow()) = new Queen(color);
		else if (m.getDestRow() == 0 && color == BLACK)
			(*this)(m.getDestCol(), m.getDestRow()) = new Queen(color);
		else
			(*this)(m.getDestCol(), m.getDestRow()) = new Pawn(color);
		break;
	case 'N': case 'n': // knight
		(*this)(m.getDestCol(), m.getDestRow()) = new Knight(color); break;
	case 'B': case 'b': // bishop
		(*this)(m.getDestCol(), m.getDestRow()) = new Bishop(color); break;
	case 'R': case 'r': // rook
		(*this)(m.getDestCol(), m.getDestRow()) = new Rook(color); break;
	case 'Q': case 'q': // queen
		(*this)(m.getDestCol(), m.getDestRow()) = new Queen(color); break;
	case 'K': case 'k': // king

		// castling
		char idealColor = ((color) ? 'R' : 'r');
		if (destMove && destMove.getPiece().getType() == idealColor) {
			// init new pieces
			(*this)(m.getDestCol(), m.getDestRow()) = new King(color);
			(*this)(m.getSrcCol(), m.getSrcRow()) = new Rook(color);
			(*this)(m.getDestCol(), m.getDestRow()).getPiece().setMoved(true);
			(*this)(m.getSrcCol(), m.getSrcRow()).getPiece().setMoved(true);

			return;
		}
		else (*this)(m.getDestCol(), m.getDestRow()) = new King(color); // normal move
		break;
	}

	// mark the piece as moved
	(*this)(m.getDestCol(), m.getDestRow()).getPiece().setMoved(true);

	// destroy original tile
	(*this)(m.getSrcCol(), m.getSrcRow()).reset();

	// store the move last made
	lastMove = &m;
}

bool Board::determineCheckmate(bool color) {
	if (determineCheck(color)) {
		std::vector<Move> moveList = getAllMoves(!color);

		// find all next-step board states
		for (int i = 0; i < moveList.size(); i++) {
			Board copy(*this);
			copy.movePiece(moveList[i]);

			// if escape is possible, return false
			if (!copy.determineCheck(color)) return false;
		}
		return true;
	}

	return false; // no check found
}

bool Board::determineCheck(bool color) {
	// opponent moves
	std::vector<Move> moveList = getAllNonKingMoves(color);
	for (int i = 0; i < moveList.size(); i++) {
		Tile t = (*this)(moveList[i].getDestCol(), moveList[i].getDestRow());
		if (t && t.getPiece().getType() == ((color) ? 'K' : 'k')) return true;
	}

	return false; // not check
}

bool Board::determineStalemate(bool color) {
	// if check cannot be stalemate
	if (determineCheck(color)) return false;
	// if no possible moves, stalemate
	if (getAllMoves(!color).size() == 0) return true;

	return false; // else must be stalemate
}

bool Board::determineDraw() {
	// determine if two kings are only pieces left
	int boardValue = 0;
	for (unsigned i = 0; i < BOARD_S; i++)
		for (unsigned j = 0; j < BOARD_S; j++)
			if ((*this)(j, i))
				boardValue += (*this)(j, i).getPiece().getValue();

	// if board value is equal to two kings, draw
	return (boardValue == 2 * Params::KING);
}

std::vector<Move> Board::getAllMoves(bool color) {
	std::vector<Move> moveList;

	for (unsigned i = 0; i < BOARD_S; i++) {
		for (unsigned j = 0; j < BOARD_S; j++) {
			if (!(*this)(j, i) || (*this)(j, i).getPiece().getColor() == color) continue;

			// get possible moves for each piece
			std::vector<Move> m = (*this)(j, i).getPiece().getMoves(this, j, i);
			for (unsigned k = 0; k < m.size(); k++)
				moveList.push_back(m[k]);
		}
	}
	return moveList;
}

// returns all moves for a player except for king
std::vector<Move> Board::getAllNonKingMoves(bool color) {
	std::vector<Move> moveList;
	for (unsigned i = 0; i < BOARD_S; i++)
		for (unsigned j = 0; j < BOARD_S; j++) {
			if (!(*this)(j, i) || (*this)(j, i).getPiece().getColor() == color) continue;

			// ignore kings
			if ((*this)(j, i).getPiece().getType() == ((color) ? 'k' : 'K')) continue;

			// get possible moves for each piece
			std::vector<Move> m = (*this)(j, i).getPiece().getMoves(this, j, i);
			for (unsigned k = 0; k < m.size(); k++)
				moveList.push_back(m[k]);
		}


	return moveList;
}

int Board::getAllPieceValues(bool color) {
	int count = 0;
	for (unsigned i = 0; i < BOARD_S; i++)
		for (unsigned j = 0; j < BOARD_S; j++)
			if ((*this)(j, i)) {
				// if piece exists and right color
				if ((*this)(j, i).getPiece().getColor() == color)
					count += (*this)(j, i).getPiece().getValue();
				else
					count -= (*this)(j, i).getPiece().getValue();
			}

	return count;
}

int Board::getAllMobilityValues(bool color) {
	int count = 0;
	for (unsigned i = 0; i < BOARD_S; i++)
		for (unsigned j = 0; j < BOARD_S; j++) {
			if (!(*this)(j, i)) continue; // skip empty tiles

			// if piece exists and right color
			if ((*this)(j, i).getPiece().getColor() == color)
				count += (*this)(j, i).getPiece().getMoves(this, j, i).size();
			else
				count -= (*this)(j, i).getPiece().getMoves(this, j, i).size();
		}

	return count;
}


int Board::getAllPawnValues(bool color) {
	int count = 0;
	for (unsigned i = 0; i < BOARD_S; i++)
		for (unsigned j = 0; j < BOARD_S; j++)
			if ((*this)(j, i))
				if ((*this)(j, i).getPiece().getValue() == Params::PAWN)
				{
					if ((*this)(j, i).getPiece().getColor() == color)
						count += ((color == WHITE) ? i - 1 : 6 - i); // white pawns
					else
						count -= ((color == WHITE) ? 6 - i : i - 1); // black pawns
				}

	return count;
}

// get all piece square values
int Board::getAllPieceSquareValues(bool color) {
	int count = 0;
	for (unsigned i = 0; i < BOARD_S; i++)
		for (unsigned j = 0; j < BOARD_S; j++)
			if ((*this)(j, i)) {
				// if piece exists and right color
				if ((*this)(j, i).getPiece().getColor() == color)
					count += (*this)(j, i).getPiece().getSquareValue(j, i);
				else
					count -= (*this)(j, i).getPiece().getSquareValue(j, i);
			}

	return count;
}


void Board::printBoard(int selectedCol, int selectedRow, std::vector<std::pair<int, int>> moves) {
	system("stty cooked");
	std::cout << "\033c";

	const std::string WHITE = "\033[30;47m";
	const std::string BLACK = "\033[37;40m";
	const std::string BLUE = "\033[37;44m";
	const std::string GREEN = "\033[37;42m";
	const std::string END = "\033[0m";

	std::cout << "\n  ";

	std::string color;
	for (int i = BOARD_S; i > 0; i--) {
		std::cout << i << "   ";
		for (int j = 0; j < BOARD_S; j++) {
			if (selectedCol == j && selectedRow == i - 1)
				color = BLUE;
			else if (std::find(moves.begin(), moves.end(), std::make_pair(j, i - 1)) != moves.end())
				color = GREEN;
			else
				color = (i % 2 == 0) ? ((j % 2 == 0) ? WHITE : BLACK) : ((j % 2 == 0) ? BLACK : WHITE);

			std::cout << color << " " << (*this)(j, i - 1) << " " << END;
		}
		std::cout << "\n  ";
	}
	std::cout << "\n       ";

	// column labels
	for (int i = 0; i < BOARD_S; i++)
		std::cout << (char)(97 + i) << "  ";

	// message
	std::cout << "\n" << message << "\n";
	system("stty raw");
}

void Board::setMessage(std::string message) {
	this->message = message;
}

Tile& Board::operator()(int c, int r) {
	return tiles[c][r];
}

Tile const& Board::operator()(int c, int r) const {
	return tiles[c][r];
}