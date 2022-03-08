#include "game.hh"
#include "human.hh"
#include "engine.hh"

const bool WHITE = true, BLACK = false;

int main() {
    Board* board = new Board();
    Player* white; Player* black;

    int depth;
    std::cout << "depth: ";
    std::cin >> depth;

    white = new Human(WHITE);
    black = new Engine(BLACK, depth);

    Game game(board, white, black);
    game.play();
    return 0;
}
