#include "engine.hh"

Engine::Engine(bool color, unsigned depth) {
    setColor(color);
    setDepth(depth);
}

Move Engine::getMove() {
    std::cout << "Engine is thinking...\n";
    return search(INT_MIN, INT_MAX);
}

Move Engine::search(int alpha, int beta) {
    // get possible engine moves
    std::vector<Move> moveList = getBoard()->getAllMoves(!getColor());
    removeCheckedMoves(moveList); // filter out moves that would put the engine in check

    std::vector<Move> bestMoves;
    int bestMoveValue = INT_MIN;
    for (unsigned i = 0; i < moveList.size(); i++) {
        std::string toFind = moveList[i].stateMove();
        if (std::find(buffer.begin(), buffer.end(), toFind) != buffer.end()) continue; // if in buffer, skip

        Board* copy = new Board(*getBoard());
        copy->movePiece(moveList[i]);
        int v = -negamax(copy, depth - 1, -beta, -alpha, !getColor());
        delete copy;

        // if same vale as best move, add to list
        if (v == bestMoveValue || moveList.size() <= Params::BUFFER_SIZE)
            bestMoves.push_back(moveList[i]);

        // if best, update best move value
        else if (v > bestMoveValue) {
            bestMoveValue = v;
            bestMoves.clear(); // clear worse moves
            bestMoves.push_back(moveList[i]);
        }
        if (bestMoveValue > alpha) alpha = bestMoveValue;

        // beta cutoff
        if (alpha >= beta) {
            pruneCount++;
            break;
        }
    }

    // if no moves, forfeit game
    if (bestMoves.size() == 0) {
        std::cout << (getColor() ? "White" : "Black");
        std::cout << " has forfeited the game.\n\n";
        exit(0);
    }

    // if equal best moves, choose randomly
    Move theBestMove = bestMoves[rand() % bestMoves.size()];
    buffer.push_back(theBestMove.stateMove()); // add best to buffer

    if (buffer.size() > Params::BUFFER_SIZE)
        buffer.erase(buffer.begin());

    // find the value of that move
    Board* copy = new Board(*getBoard());
    copy->movePiece(theBestMove);

    // if checkmate
    if (copy->determineCheckmate(!getColor()))
        bestMoveValue = Params::CHECKMATE;
    // if stalemates
    else if (copy->determineStalemate(!getColor()))
        bestMoveValue = Params::STALEMATE;
    // if  draws
    else if (copy->determineDraw())
        bestMoveValue = Params::DRAW;
    // if check
    else if (copy->determineCheck(!getColor()))
        bestMoveValue = Params::CHECK * evaluate(copy);
    else
        bestMoveValue = evaluate(copy);

    delete copy;

    // display info
    getBoard()->setMessage(moveData(theBestMove, bestMoveValue, bestMoves.size()));
    return theBestMove;
}

int Engine::negamax(Board* board, unsigned depth, int alpha, int beta, bool player) {
    evalCount++;
    int perspective = (player == getColor() ? 1 : -1);
    if (depth == 0) return perspective * evaluate(board);

    // checkmate worst
    if (board->determineCheckmate(player)) return -Params::CHECKMATE;
    // stalemate neutral
    if (board->determineStalemate(player)) return Params::STALEMATE;
    // draw neutral
    if (board->determineDraw()) return Params::DRAW;
    // checking is good
    if (board->determineCheck(player)) return (Params::CHECK * perspective) * evaluate(board);


    int value = INT_MIN;

    // opponent moves	
    std::vector<Move> moveList = board->getAllMoves(!player);
    for (unsigned i = 0; i < moveList.size(); i++) {
        Board* copy = new Board(*board);
        copy->movePiece(moveList[i]);
        int v = -negamax(copy, depth - 1, -beta, -alpha, !player);
        delete copy;
        value = std::max(value, v);
        alpha = std::max(alpha, value);
        if (alpha >= beta) { // beta cutoff
            pruneCount++;
            break;
        }
    }
    return value;
}


int Engine::evaluate(Board* board) {
    int value = board->getAllPieceValues(getColor()); // material value
    int mobility = board->getAllMobilityValues(getColor()); // board control
    int pawns = board->getAllPawnValues(getColor()); // pawn control
    int squareValues = board->getAllPieceSquareValues(getColor()); // tile control


    // weigthed sum
    int c1 = Params::C1, c2 = Params::C2, c3 = Params::C3, c4 = Params::C4;
    return (c1 * value) + (c2 * mobility) + (c3 * pawns) + (c4 * squareValues);
}

std::string Engine::moveData(Move m, int score, unsigned moves) {
    std::stringstream ss;
    ss << (getColor() ? "White(" : "Black(") << depth << "): " << m.stateMove();
    ss << "Score: " << score << "\n";
    ss << "Evaluated: " << evalCount << "\n";
    ss << "Pruned: " << pruneCount << "\n";
    evalCount = 0; pruneCount = 0;
    return ss.str();
}

void Engine::setDepth(unsigned d) { depth = d; }
