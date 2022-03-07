#include "player.hh"

class Human : public Player {
public:
    Human(bool);
    Move promptMove();

private:
    void errorMessage(int);
    bool verifyInput(std::string);
    bool verifyShow(std::string);
    bool verifyMove(Move, std::vector<Move>);
    bool checkOwner(unsigned, unsigned);
    bool checkPiece(unsigned, unsigned);
    void quitGame();
};
