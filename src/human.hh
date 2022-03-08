#include "player.hh"

class Human : public Player {
public:
    Human(bool);
    Move promptMove();
};
