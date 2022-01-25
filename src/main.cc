#include <iostream>
#include <fcntl.h>
#include <string>
#include <list>
#include "user_interface.hh"
#include "move.hh"
#include "state.hh"

#include <locale>
#include <codecvt>


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