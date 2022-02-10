#include "user_interface.hh"

#include <fcntl.h>

#include <iostream>
#include <string>

#include "move.hh"

UserInterface* UserInterface::instance = 0;

UserInterface* UserInterface::Instance() {
    if (instance == 0) instance = new UserInterface();
    return instance;
}

void UserInterface::DrawBoard() {
    system("clear");
    std::wcout << "\n";
    int counter = 0;
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        std::wcout << i + 1 << " ";

        for (int j = 0; j < BOARD_SIZE; j++) {
            std::wstring symbol;

            if (_state->board[j][i] != NULL) {
                if (_state->board[j][i]->GetColor() == 1) {
                    symbol = L"\x1B[30m";
                    symbol += _state->board[j][i]->GetLetter();
                    symbol += L" \033[0m";
                }
                else {
                    symbol = L"\x1B[37m";
                    symbol += _state->board[j][i]->GetLetter();
                    symbol += L" \033[0m";
                }

                if (counter % 2 == 0)
                    std::wcout << L"\x1B[100m " << symbol << "\033[0m";
                else
                    std::wcout << L"\x1B[42m " << symbol << "\033[0m";
            }
            else if (counter % 2 == 0)
                std::wcout << L"\x1B[100m " << " "
                << " \033[0m";
            else
                std::wcout << L"\x1B[42m " << " "
                << " \033[0m";
            counter++;
        }
        counter++;
        std::wcout << L"\n";
    }
    std::wcout << "   a  b  c  d  e  f  g  h";
}

Move UserInterface::GiveOpponentMove() {
    std::string input;
    char p;
    int startCol, endCol;
    std::wcout << L"\nMove: ";
    std::cin >> input;

    startCol = ReturnCharIndex(input[0]);
    endCol = ReturnCharIndex(input[2]);

    Tile startTile(startCol, (input[1] - '0') - 1);
    Tile endTile(endCol, (input[3] - '0') - 1);

    return Move(startTile, endTile);
}

bool UserInterface::AskPlayerSide() {
    std::wcout << L"\nChoose side [w/b]: ";
    char side;
    std::cin >> side;
    return (side == 'w');
}

int UserInterface::ReturnCharIndex(char& c) {
    char col[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    for (int i = 0; i < 8; i++)
        if (c == col[i]) return i;

    return -1;
}
