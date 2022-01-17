#include <iostream>
#include <string>
#include <fcntl.h>
#include <iostream>
#include "user_interface.hh"
#include "move.hh"



UserInterface* UserInterface::instance = 0;


UserInterface* UserInterface::Instance()
{
    if (instance == 0)
        instance = new UserInterface();
    return instance;
}

void UserInterface::DrawBoard()
{
    int counter = 0;
    for (int i = 0; i < 8; i++) {
        std::wcout << i + 1 << " ";

        for (int j = 0; j < 8; j++)
        {
            std::wstring symbol;

            if (_state->board[j][i] != NULL) {
                if (_state->board[j][i]->GetColor() == 1)
                    symbol = L"\x1B[30m" + _state->board[j][i]->GetUnicode() + L" \033[0m";
                else
                    symbol = _state->board[j][i]->GetUnicode() + L" ";


                if (counter % 2 == 0)
                    std::wcout << L"\x1B[47m" << symbol << "\033[0m";
                else
                    std::wcout << L"\x1B[42m" << symbol << "\033[0m";


            }
            else
                if (counter % 2 == 0)
                    std::wcout << L"\x1B[47m" << "  " << "\033[0m";
                else
                    std::wcout << L"\x1B[42m" << "  " << "\033[0m";
            counter++;
        }
        counter++;
        std::wcout << "\n";
    }
    std::wcout << "  a b c d e f g h";
}

Move UserInterface::GiveOpponentMove()
{
    Move move;
    return move;
}

int UserInterface::AskOpponentColor()
{
    /*     char ans;
        std::cout << "W/B: ";
        std::cin >> ans;
        return ans = ("W") ? 1 : 0; */

    return 0;
}
