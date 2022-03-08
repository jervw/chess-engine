#include "player.hh"

bool Player::getColor() { return color; }
Board* Player::getBoard() { return board; }

void Player::setColor(bool c) { color = c; }
void Player::setBoard(Board* b) { board = b; }