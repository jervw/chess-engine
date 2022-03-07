#include <algorithm>
#include <iostream>
#include "board.hh"
#include "game.hh"
#include "pieces.hh"


Board::Board() {

}

Board::~Board() {

}

void Board::initBoard() {


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
