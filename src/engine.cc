#include <iostream>
#include <random>

#include "game.hh"
#include "engine.hh"

Engine::Engine(Color color, Board* board) : board(board), engineColor(color) {}
Engine::~Engine() = default;

bool Engine::play() {
    std::vector<Piece*> pieces = board->getPieces(engineColor);

    for (auto* piece : pieces) {
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles)
            moves.push_back(std::make_pair(piece, tile));

    }

    /*     // temporary random engine
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<int> dist(0, moves.size() - 1);

        int randomIndex = dist(g);
        */




        //bool success = board->movePiece(piece->getRow(), piece->getCol(), tile.getRow(), tile.getCol());
    if (1) {
        Game::Instance()->setMessage(movesToString(moves)); // set message
        moves.clear();
        return 1;
    }

    return 0;
}


int Engine::mini(int depth) {
    if (depth == 0) return -evaluate();
    int min = +1000000;
    for (auto move : moves) {
        int score = maxi(depth - 1);
        if (score < min) min = score;
    }
    return min;
}

int Engine::maxi(int depth) {
    if (depth == 0) return evaluate();
    int max = -1000000;
    for (auto move : moves) {
        int score = mini(depth - 1);
        if (score > max) max = score;
    }
    return max;
}

int Engine::miniAlphaBeta(int depth, int alpha, int beta) {
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

int Engine::maxiAlphaBeta(int depth, int alpha, int beta) {
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



int Engine::evaluate() {
    int score = 0;
    int blackPiecePoints = 0;
    int whitePiecePoints = 0;
    for (auto piece : board->getPieces(WHITE)) {
        whitePiecePoints += piece->getValue();
    }
    for (auto piece : board->getPieces(BLACK)) {
        blackPiecePoints += piece->getValue();
    }

    score = whitePiecePoints - blackPiecePoints;

    for (auto move : moves) {
        Piece* piece = move.first;
        Tile tile = move.second;
        score += piece->getValue() * (tile.getRow() - piece->getRow());
    }





    return score;
}



std::string Engine::movesToString(const std::vector<std::pair<Piece*, Tile>>&moves) {
    std::string str;
    for (auto move : moves) {
        str += Game::Instance()->columnToChar(move.first->getCol()) + std::to_string(move.first->getRow());
        str += Game::Instance()->columnToChar(move.second.getCol()) + std::to_string(move.second.getRow());
        str += "  ";
    }
    return str;
}