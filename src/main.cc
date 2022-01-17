#include <iostream>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <list>
#include "user_interface.hh"
#include "move.hh"
// #include "state.hh"

#include <locale>
#include <codecvt>


int main() {

  // Set locale to support GNU/Linux
  std::ios_base::sync_with_stdio(false);
  std::locale utf8(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
  std::wcout.imbue(utf8);


  std::wcout << "Jeren super-shakki :D\n";
  std::wcout << L"Welcome to play\n";


  State state;
  UserInterface::Instance()->SetState(&state);

  Game game(UserInterface::Instance()->AskOpponentColor());
  std::list<Move> moveList;
  int engineColor = game.GetEngineColor();

  while (1) {
    moveList.clear();
    UserInterface::Instance()->DrawBoard();
    std::wcout << "\n";
    // Tarkasta onko peli loppu?
    state.GetLegalMoves(moveList);
    if (moveList.size() == 0)
      break;
    Move move;
    if (state.GetTurn() == engineColor) {
      MinMax value;
      if (engineColor == 0) {
        value = state.Max(3);
      }
      else {
        value = state.Min(3);
      }
      move = value._bestMove;
    }
    else {
      move = UserInterface::Instance()->
        GiveOpponentMove();
    }
    state.UpdateState(&move);
  }

  std::wcout << "Game over";
  return 0;
}