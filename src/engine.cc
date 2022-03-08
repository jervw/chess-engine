
#include "engine.hh"

Engine::Engine(bool color, int depth) : depth(depth) {
    setColor(color);
}

Move Engine::play() {
    return search(INT_MIN, INT_MAX);
}

Move Engine::search(int alpha, int beta) {
    // TODO
}

int Engine::negamax(Board* board, int depth, int alpha, int beta, bool color) {
    // TODO
}

int Engine::evaluate(Board* board) {
    // TODO
}