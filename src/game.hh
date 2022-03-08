#include "player.hh"

class Game {

public:
	Game(Board*, Player*, Player*);
	~Game();
	void play();

private:
	Board* board;
	Player* white; Player* black;
	int gameState; // current game state
	int moveCount = 1; // game move counter

	void whiteMove();
	void blackMove();
	void makeMove(Move);
	Board* getBoard();

	int getGameState();

	void setGameState(int);
};
