#include "human.hh"
#include <vector>
#include <utility>

Human::Human(bool color) {
    setColor(color);
}

Move Human::getMove() {
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

                std::cout << selectedPiece->getSquareValue(currentCol, currentRow) << std::endl;
                std::cout << currentCol << " " << currentRow << std::endl;
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


void Human::moveUp() {
    (currentRow < 7) ? currentRow++ : currentRow = 0;
}

void Human::moveDown() {
    (currentRow > 0) ? currentRow-- : currentRow = 7;
}

void Human::moveLeft() {
    (currentCol > 0) ? currentCol-- : currentCol = 7;
}

void Human::moveRight() {
    (currentCol < 7) ? currentCol++ : currentCol = 0;
}

