#include "player.hh"

void Player::removeCheckedMoves(std::vector<Move>& moveList) {
    std::vector<int> indexes;
    for (unsigned i = 0; i < moveList.size(); i++) {
        // make move on a copy and check if check
        Board* copy = new Board(*getBoard());
        copy->movePiece(moveList[i]);
        if (copy->determineCheck(getColor()))
            indexes.insert(indexes.begin(), i);

        delete copy; // delete copy
    }
    for (unsigned i = 0; i < indexes.size(); i++)
        moveList.erase(moveList.begin() + indexes[i]);

    indexes.clear();
}

bool Player::getColor() { return color; }
Board* Player::getBoard() { return board; }

void Player::setColor(bool c) { color = c; }
void Player::setBoard(Board* b) { board = b; }