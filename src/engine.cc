#include <iostream>
#include <fstream>


#include "game.hh"
#include "engine.hh"

Engine::Engine(Color color, Board* board) : board(board), engineColor(color) {}
Engine::~Engine() = default;

bool Engine::play() {

    generateMoves();

    std::vector<std::pair<Piece*, Tile>> engineMoves = moves;

    // find best move
    int bestMove = 0;
    double bestScore = -1;
    for (int i = 0; i < engineMoves.size(); i++) {
        double score = evaluate();
        if (score > bestScore) {
            bestScore = score;
            bestMove = i;
        }
    }



    // make best move
    Piece* piece = moves[bestMove].first;
    Tile tile = moves[bestMove].second;
    board->movePiece(piece->getRow(), piece->getCol(), tile.getRow(), tile.getCol());

    std::string s_move = "";
    Game::Instance()->setMessage(s_move);
    moves.clear();

    return 1;
}

bool Engine::generateMoves() {
    moves.clear();
    std::vector<Piece*> pieces = board->getPieces(engineColor);

    for (auto* piece : pieces) {
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles)
            moves.push_back(std::make_pair(piece, tile));
    }


    movesToString(moves);
    return moves.size() > 0;
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


double Engine::evaluate() {
    double evaluation = materialScore();

    for (auto* piece : board->getPieces(engineColor)) {
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles)
            evaluation += piece->getTileValue(tile.getCol(), tile.getRow());
    }

    return evaluation;
}

// minimax algorithm
int Engine::minimax(int depth) {
    if (depth == 0)
        return evaluate();

    int bestScore = -1;
    std::vector<Piece*> pieces = board->getPieces(engineColor);

    for (auto* piece : pieces) {
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles) {
            board->movePiece(piece->getRow(), piece->getCol(), tile.getRow(), tile.getCol());
            int score = -minimax(depth - 1);
            board->undoMove();
            if (score > bestScore)
                bestScore = score;
        }
    }

    return bestScore;
}


void Engine::movesToString(const std::vector<std::pair<Piece*, Tile>>&moves) {
    // append to file
    std::ofstream file;
    file.open("moves.txt", std::ios::app);

    std::string str;
    for (auto move : moves) {
        str += move.first->colToChar() + std::to_string(move.first->getRow());
        str += move.second.colToChar() + std::to_string(move.second.getRow());
        str += " ";
    }

    file << str << std::endl;
    file.close();
}

