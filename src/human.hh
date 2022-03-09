#include "player.hh"

class Human : public Player {

public:
    Human(bool);
    Move getMove();
private:
    unsigned currentCol, currentRow;
    unsigned selectedCol, selectedRow;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    std::vector<Tile> getTileList(std::vector<Move>&);
};
