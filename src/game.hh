#pragma once

#include <vector>
#include <string>
#include "board.hh"

class Game {
public:
	Game();
	~Game();

	static Game* Instance();

	void setMessage(std::string msg);
	void startGame();
	char columnToChar(int);
	int getPlayerTurn();

private:
	static Game* instance;
	std::string message;
	Board* board;
	int currentTurn;
	int currentRow, currentCol;
	int selectedRow, selectedCol;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void switchPlayer();
	void drawBoard(int, int, std::vector<Tile>&);
};

