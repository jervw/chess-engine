#include <iostream>

#include "game.hh"
#include "engine.hh"

Engine::Engine(Color color, Board* board) : board(board), engineColor(color) {}
Engine::~Engine() = default;

bool Engine::play() {
    std::vector<Piece*> pieces = board->getPieces(engineColor);

    std::string pieceInfo = "";
    for (auto* piece : pieces) {
        pieceInfo += piece->pieceInfo() + "\n";
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles)
            moves.push_back(std::make_pair(piece, tile));
    }


    // get best move




    Game::Instance()->setMessage(pieceInfo);
    return 1;
}

double Engine::materialScore() {
    double whiteScore = 0;
    double blackScore = 0;
    for (auto* piece : board->getPieces(WHITE))
        whiteScore += piece->getMatValue();

    for (auto* piece : board->getPieces(BLACK))
        blackScore += piece->getMatValue();

    return (whiteScore - blackScore);
}


double Engine::mini(int depth) {
    if (depth == 0) return -evaluate();
    int min = +1000000;
    for (auto move : moves) {
        int score = maxi(depth - 1);
        if (score < min) min = score;
    }
    return min;
}

double Engine::maxi(int depth) {
    if (depth == 0) return evaluate();
    int max = -1000000;
    for (auto move : moves) {
        int score = mini(depth - 1);
        if (score > max) max = score;
    }
    return max;
}

double Engine::evaluate() {
    double score = materialScore();

    for (auto* piece : board->getPieces(engineColor)) {
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles)
            score += piece->getTileValue(tile.getCol(), tile.getRow());

    }

    return score / 100;
}

std::string Engine::movesToString(const std::vector<std::pair<Piece*, Tile>>&moves) {
    std::string str;
    for (auto move : moves) {
        str += Game::Instance()->columnToChar(move.first->getCol()) + std::to_string(move.first->getRow());
        str += Game::Instance()->columnToChar(move.second.getCol()) + std::to_string(move.second.getRow());
    }
    return str;
}



// Alpha-Beta Prunning
double Engine::miniAlphaBeta(int depth, int alpha, int beta) {
    if (depth == 0) return -evaluate();
    int min = +1000000;
    for (auto move : moves) {
        int score = maxiAlphaBeta(depth - 1, alpha, beta);
        if (score < min) min = score;
        if (min <= alpha) return alpha;
        beta = std::min(beta, min);
    }
    return min;
}

double Engine::maxiAlphaBeta(int depth, int alpha, int beta) {
    if (depth == 0) return evaluate();
    int max = -1000000;
    for (auto move : moves) {
        int score = miniAlphaBeta(depth - 1, alpha, beta);
        if (score > max) max = score;
        if (max >= beta) return max;
        if (max > alpha) alpha = max;
    }
    return max;
}