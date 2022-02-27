#include <iostream>
#include <string>
#include "game.hh"

int main() {

	// TODO ask player who is going to start the game

	Game::Instance()->startGame();
	return 0;
}