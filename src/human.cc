#include "human.hh"

Human::Human(bool color) {
    setColor(color);
}

Move Human::promptMove() {
    // IMPLEMENT
    std::string s;
    std::cin >> s;


    return Move();
}

