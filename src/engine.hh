#include "player.hh"
#include <limits.h>
#include <algorithm>

class Engine : public Player {

public:
    Engine(bool, unsigned);
    Move getMove();

private:
    unsigned depth; // depth for minimax algorithm
    unsigned evalCount = 0; // number of evaluations
    unsigned pruneCount = 0; // number of prunes
    std::vector<std::string> buffer; // move buffer

    Move search(int, int);
    int negamax(Board*, unsigned, int, int, bool);
    int evaluate(Board*);

    std::string moveData(Move, int, unsigned);

    void setDepth(unsigned);

};
