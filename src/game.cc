#include "game.hh"

Game::Game(Board* board, Player* white, Player* black) : board(board), white(white), black(black), gameState(0) {
	white->setBoard(board);
	black->setBoard(board);
}

Game::~Game() {
	delete board;
	delete white;
	delete black;

	// restore terminal settings
	system("stty echo");
	system("stty cooked");
}

// main game loop
void Game::play() {
	while (1) {
		getBoard()->printBoard();

		whiteMove(); // else white can move
		getBoard()->printBoard();

		blackMove(); // else black can move
	}
	// OUT of the game loop

	switch (getGameState()) {
	case 1: std::cout << "\nStalemate.\n\n"; break;
	case 2: std::cout << "\nDraw.\n\n"; break;
	case 3: std::cout << "\nBlack checkmates white.\n\n"; break;
	case 4: std::cout << "\nWhite checkmates black.\n\n"; break;
	}
}

// white move
void Game::whiteMove() {
	Move m = white->getMove();
	makeMove(m); // make the move
}

// black move function
void Game::blackMove() {
	Move m = black->getMove();
	makeMove(m); // make the move
}

void Game::makeMove(Move move) {
	getBoard()->movePiece(move);
	moveCount++;
}

Board* Game::getBoard() { return board; }
int Game::getGameState() { return gameState; }

void Game::setGameState(int s) { gameState = s; }
