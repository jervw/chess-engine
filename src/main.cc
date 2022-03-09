#include <string.h>
#include "game.hh"
#include "human.hh"
#include "engine.hh"

const bool WHITE = true, BLACK = false;

int main(int argc, char** argv) {
    Board* board = new Board();
    Player* white; Player* black;

    if (argc > 2) {
        int depth = atoi(argv[2]);
        if (strcmp(argv[1], "--white") == 0) {
            white = new Human(WHITE);
            black = new Human(BLACK);
            //black = new Engine(BLACK, depth);
        }
        else if (strcmp(argv[1], "--black") == 0) {
            white = new Engine(WHITE, depth);
            black = new Human(BLACK);
        }
        else if (strcmp(argv[1], "--engine") == 0) {
            white = new Engine(WHITE, depth);
            black = new Engine(BLACK, depth);
        }
        else {
            std::cerr << "Invalid arguments, use --white, --black or --engine followed by depth" << std::endl;
            return 1;
        }

        // Start game
        Game game(board, white, black);
        game.play();
        return 0;
    }
    else {
        std::cerr << "Invalid arguments, use --white, --black or --engine followed by depth" << std::endl;
        return 1;
    }
}
