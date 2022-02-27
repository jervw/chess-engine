#include <iostream>
#include <random>

#include "game.hh"
#include "engine.hh"
#include <time.h>

Engine::Engine(Color color, Board* board) : board(board), engineColor(color) {}
Engine::~Engine() = default;

bool Engine::play() {
    std::vector<Piece*> pieces = board->getPieces(engineColor);

    for (auto* piece : pieces) {
        std::vector<Tile> possibleTiles = piece->getPossibleTiles(*board);
        for (auto tile : possibleTiles)
            moves.push_back(std::make_pair(piece, tile));

    }

    // temporary random engine
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> dist(0, moves.size() - 1);

    int randomIndex = dist(g);
    Piece* piece = moves[randomIndex].first;
    Tile tile = moves[randomIndex].second;

    bool success = board->movePiece(piece->getRow(), piece->getCol(), tile.getRow(), tile.getCol());
    if (success) {
        Game::Instance()->setMessage(movesToString(moves)); // set message
        moves.clear();
        return 1;
    }

    return 0;
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