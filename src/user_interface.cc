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
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (_state->board[i][j] != NULL) std::wcout << _state->board[i][j]->GetUnicode() << "\n";
        }

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
