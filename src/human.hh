#include "player.hh"

class Human : public Player {

public:
    Human(bool, bool);
    Move getMove();
    Move promptMove();
private:
    bool mode;
    unsigned currentCol, currentRow;
    unsigned selectedCol, selectedRow;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void errorMessage(unsigned);
    bool verifyInput(std::string);
    bool verifyShow(std::string);
    bool verifyMove(Move, std::vector<Move>);
    bool checkOwner(unsigned, unsigned);
    bool checkPiece(unsigned, unsigned);
    void quitGame();

    std::vector<Tile> getTileList(std::vector<Move>&);
};
