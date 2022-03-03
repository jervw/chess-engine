#include <iostream>

#include "game.hh"
#include "engine.hh"

Engine::Engine(Color color, Board* board) : board(board), engineColor(color) {}
Engine::~Engine() = default;

bool Engine::play() {

    generateMoves();


    // search best move 
    int bestMove = 0;
    double bestScore = -1;
    for (int i = 0; i < moves.size(); i++) {
        double score = search(3, -1, 1);
        std::cout << "Move: " << moves[i].first->getName() << " " << moves[i].second.getRow() << " " << moves[i].second.getCol() << " Score: " << score << std::endl;
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

int Engine::search(int depth, int alpha, int beta) {

    if (depth == 0) return evaluate();
    if (moves.size() == 0) return 0;  // stalemate or checkmate

    generateMoves();


    for (auto move : moves) {
        board->movePiece(move.first->getRow(), move.first->getCol(), move.second.getRow(), move.second.getCol());
        int evaluation = -search(depth - 1, -beta, -alpha);
        board->undoMove();
        if (evaluation >= beta) return beta; // beta cut-off
        alpha = std::max(alpha, evaluation);
    }

    return alpha;
}




std::string Engine::movesToString(const std::vector<std::pair<Piece*, Tile>>&moves) {
    std::string str;
    for (auto move : moves) {
        str += move.first->colToChar() + std::to_string(move.first->getRow());
        str += move.second.colToChar() + std::to_string(move.second.getRow());
    }
    return str;
}

