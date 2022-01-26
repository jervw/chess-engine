#include <fcntl.h>

#include <codecvt>
#include <iostream>
#include <list>
#include <locale>
#include <string>

#include "move.hh"
#include "state.hh"
#include "user_interface.hh"

int main() {
    std::wcout << L"Welcome to Chess!\n";

    State state;
    UserInterface::Instance()->SetState(&state);

    Game game(UserInterface::Instance()->AskPlayerSide());

    while (true) {
        UserInterface::Instance()->DrawBoard();
        Move move = UserInterface::Instance()->GiveOpponentMove();
        state.UpdateState(&move);
    }

    return 0;
}