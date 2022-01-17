#include <iostream>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <list>
#include "user_interface.hh"
#include "move.hh"
#include "state.hh"


int main() {
  std::wcout << "Jeren homo-shakki :D\n";
  std::wcout << "Welcome to play\n";

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