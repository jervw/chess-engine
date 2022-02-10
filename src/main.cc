#include <fcntl.h>

#include <codecvt>
#include <algorithm>
#include <iostream>
#include <list>
#include <locale>
#include <string>

#include "move.hh"
#include "state.hh"
#include "user_interface.hh"

int main()
{
    State state;
    UserInterface::Instance()->SetState(&state);

    while (1)
    {
        // Piirret��n lauta.
        UserInterface::Instance()->DrawBoard();

        // Generoidaan siirrot.
        std::list<Move> moveList;
        state.GetLegalMoves(moveList);
        std::wcout << moveList.size() << " siirtoa:\n";
        for (auto s : moveList)
        {
            Tile start = s.Start();
            Tile end = s.End();
            std::wcout << "(" << start.column << ", " << start.row << ") - ";
            std::wcout << "(" << end.column << ", " << end.row << ")\n";
        }

        // Kysyt��n pelaajan siirto (tarkistetaan ett� on siirtolistassa).
        Move s = UserInterface::Instance()->GiveOpponentMove();
        while (std::find(moveList.begin(), moveList.end(), s) == moveList.end())
        {
            s = UserInterface::Instance()->GiveOpponentMove();
        }

        // P�ivitet��n asema pelaajan siirrolla.
        state.UpdateState(&s);
    }

    return 0;
}
