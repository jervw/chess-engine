#include "human.hh"
#include <vector>
#include <utility>

Human::Human(bool color, bool m) {
    setColor(color);
    mode = m;
}

Move Human::getMove() {
    if (!mode) return promptMove();


    std::string s;
    // get all available moves
    std::vector<Move> moveList = getBoard()->getAllMoves(!getColor());
    removeCheckedMoves(moveList);

    Piece* selectedPiece;
    std::vector<std::pair<int, int>> movePairs;
    char input[3];

    while (1) {
        system("stty -echo");

        getBoard()->printBoard(currentCol, currentRow, movePairs);

        input[0] = getchar();

        // EXIT (keys: CTRL+C, q, Q)
        if (input[0] == 3 || input[0] == 'q' || input[0] == 'Q')
            break;

        else if (input[0] == 13) {
            selectedPiece = &(*getBoard())(currentCol, currentRow).getPiece();

            if (selectedPiece && selectedPiece->getColor() == getColor()) {
                movePairs.clear();

                selectedCol = currentCol;
                selectedRow = currentRow;

                std::vector<Move> currentMoves = selectedPiece->getMoves(getBoard(), currentCol, currentRow);
                for (auto& m : currentMoves)
                    movePairs.push_back(std::make_pair(m.getDestCol(), m.getDestRow()));
            }

            if (!selectedPiece || selectedPiece->getColor() != getColor()) {


                for (auto& m : movePairs)
                    if (m.first == currentCol && m.second == currentRow) {
                        system("stty cooked");
                        system("stty echo");
                        return Move(selectedCol, selectedRow, m.first, m.second);
                    }
            }

            continue;
        }

        else if (input[0] != 27) continue; // ESC

        input[1] = getchar();
        input[2] = getchar();

        if (input[0] == 27 && input[1] == 91) {
            switch (input[2]) {
            case 65: moveUp(); break;
            case 66: moveDown(); break;
            case 67: moveRight(); break;
            case 68: moveLeft(); break;
            }
        }
    }

    system("stty cooked");
    system("stty echo");
    exit(0);
}

Move Human::promptMove() {
    system("stty cooked");
    system("stty echo");
    std::string s;
    // get all available moves
    std::vector<Move> moveList = getBoard()->getAllMoves(!getColor());
    removeCheckedMoves(moveList);
    while (1) {
        std::cout << "\n";
        std::cout << "Enter a move (e.g. a2a4)\n";
        std::cout << "Or \"quit\" to quit game.\n\n";
        std::cout << "Input: "; std::cin >> s;
        if (s.size() != 2 && s.size() != 4) { errorMessage(1); continue; }
        // if quitting game
        if (s == "quit") { quitGame(); }
        // if invalid coordinates
        if (!verifyInput(s)) { errorMessage(2); continue; }
        // if no piece on origin tile
        if (!checkPiece(s[0] - 97, s[1] - 49)) { errorMessage(3); continue; }
        // if don't own tile
        if (!checkOwner(s[0] - 97, s[1] - 49)) { errorMessage(4); continue; }
        if (s.size() == 2) continue;

        // verify move is legal
        Move m(s[0] - 97, s[1] - 49, s[2] - 97, s[3] - 49);
        if (!verifyMove(m, moveList)) { errorMessage(5); continue; }
        // if it gets here, the move is valid, so make it
        break;
    }
    return Move(s[0] - 97, s[1] - 49, s[2] - 97, s[3] - 49);
}

bool Human::checkPiece(unsigned col, unsigned row) {
    return (*getBoard())(col, row);
}

bool Human::checkOwner(unsigned col, unsigned row) {
    return getColor() == (*getBoard())(col, row).getPiece().getColor();
}

bool Human::verifyInput(std::string s) {
    if (s[0] < 97 || s[0] > 104) return false; // if column is out of range
    if (s[1] < 49 || s[1] > 56) return false; // if row is out of range
    if (s.size() == 4) {
        if (s[2] < 97 || s[2] > 104) return false;
        if (s[3] < 49 || s[3] > 56) return false;
    }
    return true;
}

bool Human::verifyMove(Move m, std::vector<Move> moves) {
    for (unsigned int i = 0; i < moves.size(); i++)
        if (moves[i] == m) return true;
    return false;
}

inline void Human::errorMessage(unsigned i) {
    std::cout << "\n";
    switch (i) {
    case 1: std::cout << "This is not a valid input.\n"; break;
    case 2: std::cout << "This is not a valid move.\n"; break;
    case 3: std::cout << "There is no piece there.\n"; break;
    case 4: std::cout << "This piece is owned by the opponent.\n"; break;
    case 5: std::cout << "This is an illegal move.\n"; break;
    }
}


void Human::moveUp() { (currentRow < 7) ? currentRow++ : currentRow = 0; }
void Human::moveDown() { (currentRow > 0) ? currentRow-- : currentRow = 7; }
void Human::moveLeft() { (currentCol > 0) ? currentCol-- : currentCol = 7; }
void Human::moveRight() { (currentCol < 7) ? currentCol++ : currentCol = 0; }
void Human::quitGame() { exit(0); }

