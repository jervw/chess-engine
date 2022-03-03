#include <iostream>
#include <algorithm>
#include "game.hh"
#include "engine.hh"


Game::Game() {
	board = new Board();

	// disable input
	system("stty -echo");
}

Game::~Game() {
	delete board;
}

Game* Game::instance = nullptr;

Game* Game::Instance() {
	if (!instance)
		instance = new Game();
	return instance;
}


void Game::startGame() {
	Engine* engine = new Engine(BLACK, board);

	currentRow = currentCol = 1;
	selectedRow = selectedCol = -1;
	currentTurn = 1;

	std::vector<Tile> highlighted;

	char input[3];
	bool gameOver = false;
	bool canMakeMove = true;
	int movesMade = 0;
	int currentMovePosition = 0;

	while (1) {
		drawBoard(currentRow, currentCol, highlighted);
		if (gameOver) break;

		if (currentTurn == BLACK && engine->play()) {
			switchPlayer();
			continue;
		}

		input[0] = getchar();

		// CTRL-C
		if (input[0] == 3 || input[0] == 'q' || input[0] == 'Q')
			break;

		// ENTER
		else if (input[0] == 13 && canMakeMove) {
			if (selectedRow == -1) {
				Piece* sel = board->getPieceAt(currentRow, currentCol);
				if (sel != NULL && currentTurn == sel->getPlayer()) {
					highlighted = sel->getPossibleTiles(*board);
					if (highlighted.size() > 0) {
						selectedRow = currentRow;
						selectedCol = currentCol;
					}
				}
			}
			else if (currentRow == selectedRow && currentCol == selectedCol) {
				selectedRow = selectedCol = -1;
				highlighted.clear();
			}
			else if (find(highlighted.begin(), highlighted.end(), Tile(currentRow, currentCol)) != highlighted.end()) {
				bool success = board->movePiece(selectedRow, selectedCol, currentRow, currentCol);
				selectedRow = selectedCol = -1;
				highlighted.clear();

				if (success) {

					movesMade++;
					currentMovePosition++;


					// check stalemate or checkmate.
					int otherPlayer = currentTurn == 1 ? 2 : 1;
					bool movesAvailable = board->movesLeft(otherPlayer);
					bool kingSafe = board->isKingSafe(otherPlayer);
					if (!movesAvailable) {
						if (!kingSafe)
							message = (currentTurn == WHITE) ? "White" : "Black" + std::string(" wins");
						else
							message = "stalemate.";
						gameOver = true;
					}

					switchPlayer();
				}
			}
			continue;
		}

		// go back.
		else if ((input[0] == 'B' || input[0] == 'b') && selectedRow == -1) {

			if (currentMovePosition > 0) {
				board->goBack();
				currentMovePosition--;
				canMakeMove = false;
			}

			continue;
		}

		// go forward.
		else if (input[0] == 'F' || input[0] == 'f') {
			if (currentMovePosition < movesMade) {
				board->goForward();
				currentMovePosition++;
				canMakeMove = currentMovePosition == movesMade;
			}
			continue;
		}
		else if (input[0] != 27) {
			std::cout << "invalid input.\n";
			continue;
		}

		input[1] = getchar();
		input[2] = getchar();

		// arrow keys.
		if (input[0] == 27 && input[1] == 91) {
			switch (input[2]) {
			case 65: moveUp(); break;
			case 66: moveDown(); break;
			case 67: moveRight(); break;
			case 68: moveLeft(); break;
			}
		}
	}

	// restore terminal
	system("stty echo");
	system("stty cooked");
}

void Game::moveUp() {
	(currentRow < 8) ? currentRow++ : currentRow = 1;
}

void Game::moveDown() {
	(currentRow > 1) ? currentRow-- : currentRow = 8;
}

void Game::moveLeft() {
	(currentCol > 1) ? currentCol-- : currentCol = 8;
}

void Game::moveRight() {
	(currentCol < 8) ? currentCol++ : currentCol = 1;
}

void Game::switchPlayer() {
	currentTurn = currentTurn == WHITE ? BLACK : WHITE;
}

void Game::drawBoard(int currentRow, int currentCol, std::vector<Tile>& highlighted) {
	system("stty cooked");
	board->clear();
	board->printBoard(currentRow, currentCol, highlighted);

	// temp
	std::string turn = (currentTurn == WHITE) ? "[White]\n" : "[Black]\n";
	std::cout << turn << message << std::endl;
	message = "";

	system("stty raw");

}

void Game::setMessage(std::string msg) {
	message = msg;
}

/// HELPER FUNCTIONS (maybe move to board class?)

char Game::columnToChar(int col) {
	const char* cols = "abcdefgh";
	return cols[col - 1];
}