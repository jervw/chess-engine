#include <iostream>
#include "legal_moves.hh"

/*K�y state olion kaksiulotteisen taulukon x ja y suuntaiset ruudut l�pi sek� isompaan ett� pienemp��n p�in ja tarkista seuraavat asiat
1) Tile tyhj�, voi menn�
2) Ruudussa oma nappula, ei voi menn�
3) Ruudussa vastustajan nappula, voi menn� mutta pidemm�lle ei voi menn�

Saa parametrinaan moveListn johon lis�ys tehd��n
*/

void LegalMoves::GetRookLegalMoves(std::list<Move>& moveList, Tile* tile, State* state, int color) {
    int row = tile->row;
    int column = tile->column;

    //color of the pawns in start and end tiles
    int startPawnColor, endPawnColor;

    startPawnColor = state->board[row][column]->GetColor();
    // vaakarivi ruudusta eteenp�in
    for (int i = row + 1; i < BOARD_SIZE; i++) {
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[i][column] == NULL) {
            moveList.push_back(Move(*tile, Tile(i, column)));
        }
        else if (state->board[i][column] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endPawnColor = state->board[i][column]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(i, column)));
                break;
            }
        }
    }
    // vaakarivi ruudusta taaksep�in
    for (int i = row - 1; i >= 0; i--) {
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[i][column] == NULL) {
            moveList.push_back(Move(*tile, Tile(i, column)));
        }
        else if (state->board[i][column] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endPawnColor = state->board[i][column]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(i, column)));
                break;
            }
        }
    }
    // pystyrivi ruudusta eteenp�in
    for (int i = column + 1; i < 8; i++) {
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[row][i] == NULL) {
            moveList.push_back(Move(*tile, Tile(row, i)));
        }
        else if (state->board[row][i] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endPawnColor = state->board[row][i]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(row, i)));
                break;
            }
        }
    }
    // pystyrivi ruudusta taaksep�in
    for (int i = column - 1; i >= 0; i--) {
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[row][i] == NULL) {
            moveList.push_back(Move(*tile, Tile(row, i)));
        }
        else if (state->board[row][i] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endPawnColor = state->board[row][i]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(row, i)));
                break;
            }
        }
    }
    // testausta varten
    // Huom. uuden standardin mukaista c++ koodia, auto-m��re antaa k��nt�j�n p��tell� luokan, k�ytt�� iteraattoreita
    /*for (auto s : moveList)
    {
        std::wcout << L"Torni";
        std::wcout << s.getAlkutile().column();
        std::wcout << s.getAlkutile().row << "-";

        std::wcout << s.End().column();
        std::wcout << s.End().row << "\n";
    }*/

}
void LegalMoves::GetBishopLegalMoves(std::list<Move>& moveList, Tile* tile, State* state, int color) {

    int column = tile->column;
    int row = tile->row;

    int startPawnColor;
    int endTileColor;

    int j;

    startPawnColor = state->board[row][column]->GetColor();

    // viistorivi ruudusta oikealle yl�s
    for (int i = row + 1; i < 8; i++) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == row + 1) {
            j = column + 1;
        }
        if (j < 0 || j > 7 || i < 0 || i > 7) {
            break;
        }
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[i][j] == NULL) {
            moveList.push_back(Move(*tile, Tile(i, j)));
        }
        else if (state->board[i][j] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endTileColor = state->board[i][j]->GetColor();
            if (startPawnColor == endTileColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }

        }
        j++;
    }

    // viistorivi ruudusta oikealle alas
    for (int i = row + 1; i < 8; i++) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == row + 1) {
            j = column - 1;
        }
        if (j < 0 || j > 7 || i < 0 || i > 7) {
            break;
        }
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[i][j] == NULL) {
            moveList.push_back(Move(*tile, Tile(i, j)));
        }
        else if (state->board[i][j] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endTileColor = state->board[i][j]->GetColor();
            if (startPawnColor == endTileColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }
        }

        j--;
    }

    // viistorivi ruudusta vasemmalle yl�s
    for (int i = row - 1; i >= 0; i--) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == row - 1) {
            j = column + 1;
        }
        if (j < 0 || j > 7 || i < 0 || i > 7) {
            break;
        }
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[i][j] == NULL) {
            moveList.push_back(Move(*tile, Tile(i, j)));
        }
        else if (state->board[i][j] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endTileColor = state->board[i][j]->GetColor();
            if (startPawnColor == endTileColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }
        }

        j++;
    }
    // viistorivi ruudusta vasemmalle alas
    for (int i = row - 1; i >= 0; i--) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == row - 1) {
            j = column - 1;
        }
        if (j < 0 || j > 7 || i < 0 || i > 7) {
            break;
        }
        // Jos tyhj� tile niin lis�t��n moveListan
        if (state->board[i][j] == NULL) {
            moveList.push_back(Move(*tile, Tile(i, j)));
        }
        else if (state->board[i][j] != NULL) {
            // Jos oma nappula niin poistutaan for silmukasta. Ei lis�t� moveListan
            // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
            endTileColor = state->board[i][j]->GetColor();
            if (startPawnColor == endTileColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }
        }

        j--;
    }
    // testausta varten
    // Huom. uuden standardin mukaista c++ koodia, auto-m��re antaa k��nt�j�n p��tell� luokan, k�ytt�� iteraattoreita
    /*for (auto s : moveList)
    {
        std::wcout << L"L�hetti";
        std::wcout << s.getAlkutile().column();
        std::wcout << s.getAlkutile().row << "-";

        std::wcout << s.End().column();
        std::wcout << s.End().row << "\n";
    }*/
}
void LegalMoves::GetQueenLegalMoves(std::list<Move>& moveList, Tile* tile, State* state, int color) {
    this->GetBishopLegalMoves(moveList, tile, state, color);
    this->GetRookLegalMoves(moveList, tile, state, color);
    /*for (auto s : moveList)
    {
        std::wcout << L"Daami";
        std::wcout << s.getAlkutile().column();
        std::wcout << s.getAlkutile().row << "-";

        std::wcout << s.End().column();
        std::wcout << s.End().row << "\n";
    }*/
}
void LegalMoves::GetKnightLegal(std::list<Move>& moveList, Tile* tile, State* state, int color) {
    int column = tile->column;
    int row = tile->row;

    int startPawnColor;
    int endTileColor;

    startPawnColor = state->board[row][column]->GetColor();

    // Pit�� huomioida ett� kokeiltavat ruudut ovat viel� laudalla
    if (row + 1 < 8 && column + 2 < 8) {
        if (state->board[row + 1][column + 2] == NULL) {
            moveList.push_back(Move(*tile, Tile(row + 1, column + 2)));
        }
        else if (state->board[row + 1][column + 2] != NULL) {
            endTileColor = state->board[row + 1][column + 2]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row + 1, column + 2)));
            }
        }
    }
    if (row + 1 < 8 && column - 2 >= 0) {
        if (state->board[row + 1][column - 2] == NULL) {
            moveList.push_back(Move(*tile, Tile(row + 1, column - 2)));
        }
        else if (state->board[row + 1][column - 2] != NULL) {
            endTileColor = state->board[row + 1][column - 2]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row + 1, column - 2)));
            }
        }
    }
    if (row - 1 >= 0 && column + 2 < 8) {
        if (state->board[row - 1][column + 2] == NULL) {
            moveList.push_back(Move(*tile, Tile(row - 1, column + 2)));
        }
        else if (state->board[row - 1][column + 2] != NULL) {
            endTileColor = state->board[row - 1][column + 2]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row - 1, column + 2)));
            }
        }
    }
    if (row - 1 >= 0 && column - 2 >= 0) {
        if (state->board[row - 1][column - 2] == NULL) {
            moveList.push_back(Move(*tile, Tile(row - 1, column - 2)));
        }
        else if (state->board[row - 1][column - 2] != NULL) {
            endTileColor = state->board[row - 1][column - 2]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row - 1, column - 2)));
            }
        }
    }
    if (row + 2 < 8 && column + 1 < 8) {
        if (state->board[row + 2][column + 1] == NULL) {
            moveList.push_back(Move(*tile, Tile(row + 2, column + 1)));
        }
        else if (state->board[row + 2][column + 1] != NULL) {
            endTileColor = state->board[row + 2][column + 1]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row + 2, column + 1)));
            }
        }
    }
    if (row + 2 < 8 && column - 1 >= 0) {
        if (state->board[row + 2][column - 1] == NULL) {
            moveList.push_back(Move(*tile, Tile(row + 2, column - 1)));
        }
        else if (state->board[row + 2][column - 1] != NULL) {
            endTileColor = state->board[row + 2][column - 1]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row + 2, column - 1)));
            }
        }
    }
    if (row - 2 >= 0 && column + 1 < 8) {
        if (state->board[row - 2][column + 1] == NULL) {
            moveList.push_back(Move(*tile, Tile(row - 2, column + 1)));
        }
        else if (state->board[row - 2][column + 1] != NULL) {
            endTileColor = state->board[row - 2][column + 1]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row - 2, column + 1)));
            }
        }
    }
    if (row - 2 >= 0 && column - 1 >= 0) {
        if (state->board[row - 2][column - 1] == NULL) {
            moveList.push_back(Move(*tile, Tile(row - 2, column - 1)));
        }
        else if (state->board[row - 2][column - 1] != NULL) {
            endTileColor = state->board[row - 2][column - 1]->GetColor();
            // jos oman v�rinen niin lis�t��n t�rmaysmoveListan
            if (startPawnColor == endTileColor) {
            }
            // jos vastujan nappula niin lis�t��n moveListan
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row - 2, column - 1)));
            }
        }
    }
    /*for (auto s : moveList)
    {
        std::wcout << L"Ratsu";
        std::wcout << s.getAlkutile().column();
        std::wcout << s.getAlkutile().row << "-";

        std::wcout << s.End().column();
        std::wcout << s.End().row << "\n";
    }*/
}
void LegalMoves::GetKingLegalMoves(std::list<Move>& moveList, Tile* tile, State* state, int color) {
    /*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
    oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

    Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eripaikassa*/


    int column = tile->column;
    int row = tile->row;

    int startPawnColor;
    int endTileColor;

    startPawnColor = state->board[row][column]->GetColor();


    // K�yd��n perusmovejen tyhj�t ruudut l�pi 
    // Pit�� tarkistaa ett� ehdokas tile viel� laudalla
    if (row + 1 < 8) {
        if (state->board[row + 1][column] == NULL) {

            moveList.push_back(Move(*tile, Tile(row + 1, column)));


        }
        else if (state->board[row + 1][column] != NULL) {
            endTileColor = state->board[row + 1][column]->GetColor();
            if (startPawnColor != endTileColor) {
                moveList.push_back(Move(*tile, Tile(row + 1, column)));
            }


        }
    }

    if (row + 1 < 8 && column + 1 < 8) {
        if (state->board[row + 1][column + 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(row + 1, column + 1)));

        }
        else if (state->board[row + 1][column + 1] != NULL) {
            endTileColor = state->board[row + 1][column + 1]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row + 1, column + 1)));

            }
        }
    }

    if (row + 1 < 8 && column - 1 >= 0) {
        if (state->board[row + 1][column - 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(row + 1, column - 1)));

        }
        else if (state->board[row + 1][column - 1] != NULL) {
            endTileColor = state->board[row + 1][column - 1]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row + 1, column - 1)));

            }
        }
    }

    if (row - 1 >= 0) {
        if (state->board[row - 1][column] == NULL) {

            moveList.push_back(Move(*tile, Tile(row - 1, column)));

        }
        else if (state->board[row - 1][column] != NULL) {
            endTileColor = state->board[row - 1][column]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row - 1, column)));

            }
        }
    }

    if (row - 1 >= 0 && column + 1 < 8) {
        if (state->board[row - 1][column + 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(row - 1, column + 1)));

        }
        else if (state->board[row - 1][column + 1] != NULL) {
            endTileColor = state->board[row - 1][column + 1]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row - 1, column + 1)));

            }
        }
    }

    if (row - 1 >= 0 && column - 1 >= 0) {
        if (state->board[row - 1][column - 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(row - 1, column - 1)));

        }
        else if (state->board[row - 1][column - 1] != NULL) {
            endTileColor = state->board[row - 1][column - 1]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row - 1, column - 1)));

            }
        }
    }

    if (column + 1 < 8) {
        if (state->board[row][column + 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(row, column + 1)));

        }
        else if (state->board[row][column + 1] != NULL) {
            endTileColor = state->board[row][column + 1]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row, column + 1)));

            }
        }
    }

    if (column - 1 >= 0) {
        if (state->board[row][column - 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(row, column - 1)));

        }
        else if (state->board[row][column - 1] != NULL) {
            endTileColor = state->board[row][column - 1]->GetColor();
            if (startPawnColor != endTileColor) {

                moveList.push_back(Move(*tile, Tile(row, column - 1)));

            }
        }
    }

}
void LegalMoves::GetCastleMoves(std::list<Move>& moveList, State* state, int color) {

    //// Linnoituksien huomioiminen
    //// 1. Kuningas ei saa olla liikkunut
    //// 2. Torni ei saa olla liikkunut
    //// 3. Kuningas ei saa olla shakattuna
    //// 4. Tilejen pit�� olla tyhj�t
    //// 5. Ruudut eiv�t saa olla uhattuja
    if (color == 0) {
        //valkean lyhyt linna
        if (!state->wKingMoved && !state->wKRookMoved
            && IsTileCucked(&Tile(4, 0), state, !color)
            && IsTileCucked(&Tile(5, 0), state, !color) && IsTileCucked(&Tile(6, 0), state, !color)
            && state->board[5][0] == NULL && state->board[6][0] == NULL) {
            //p�ivitet��n moveListan lyhytlinna
            moveList.push_back(Move(true, false)); // lis�t��n moveListan lyhyt linna
        }
        //valkean pitk� linna
        if (!state->wKingMoved && !state->wQRookMoved
            && IsTileCucked(&Tile(4, 0), state, !color)
            && IsTileCucked(&Tile(3, 0), state, !color) && IsTileCucked(&Tile(3, 0), state, !color)
            && state->board[3][0] == NULL && state->board[2][0] == NULL) {
            //p�ivitet��n moveListan lyhytlinna
            moveList.push_back(Move(false, true)); // lis�t��n moveListan lyhyt linna
        }
    }
    if (color == 1) {
        //mustan lyhyt linna
        if (!state->bKingMoved && !state->bKRookMoved
            && IsTileCucked(&Tile(4, 7), state, !color)
            && IsTileCucked(&Tile(5, 7), state, !color) && IsTileCucked(&Tile(6, 7), state, !color)
            && state->board[5][7] == NULL && state->board[6][7] == NULL) {
            //p�ivitet��n moveListan lyhytlinna
            moveList.push_back(Move(true, false)); // lis�t��n moveListan lyhyt linna
        }
        //mustan pitk� linna
        if (!state->bKingMoved && !state->bQRookMoved
            && IsTileCucked(&Tile(4, 7), state, !color)
            && IsTileCucked(&Tile(3, 7), state, !color) && IsTileCucked(&Tile(3, 7), state, !color)
            && state->board[3][7] == NULL && state->board[2][7] == NULL) {
            //p�ivitet��n moveListan lyhytlinna
            moveList.push_back(Move(false, true)); // lis�t��n moveListan lyhyt linna
        }
    }
}

void LegalMoves::GetSoldierLegalMoves(std::list<Move>& moveList, Tile* tile, State* state, int color) {
    int column = tile->column;
    int row = tile->row;
    int startPawnColor;
    int endTileColor;
    startPawnColor = state->board[row][column]->GetColor();

    // jos sotilas rivill� 2 ja sotilas valkea tai sotilas rivill� 7 ja sotilas musta sill� on kaksois askel mahdollisuus
    // muilla riveill� sotilaalla yks�is aske
    // sotilas voi my�s sy�d� etuviistoon ruudustaan
    // sotilas voi korottua jos se saavuttaa rivin 8 valkeilla ja vastaavasti rivin 1 mustilla

        // valkea rivill� 2
    if (column == 1 && startPawnColor == 0) {
        for (int i = column + 1; i < column + 3; i++) {
            // Jos tyhj� tile niin lis�t��n moveListan
            if (state->board[row][i] == NULL) {
                moveList.push_back(Move(*tile, Tile(row, i)));
            }
            else
                break;
        }
    }

    // musta rivill� 7
    if (column == 6 && startPawnColor == 1) {
        for (int i = column - 1; i > column - 3; i--) {
            // Jos tyhj� tile niin lis�t��n moveListan
            if (state->board[row][i] == NULL) {
                moveList.push_back(Move(*tile, Tile(row, i)));
            }
            else
                break;
        }
    }
    // perusruudut valkeille 
    if ((column == 2 || column == 3 || column == 4 || column == 5 || column == 6) && startPawnColor == 0) {
        //siirtym�t eteenp�in
        if (state->board[row][column + 1] == NULL) {
            if (column < 6)
                moveList.push_back(Move(*tile, Tile(row, column + 1)));
            else
                AddSoldierUpgrade(&Move(*tile, Tile(row, column + 1)), moveList, state);
        }
        //sy�nnit viistoon
        if (row + 1 < 8) { // tarkastetaan ett� pysyt��n laudalla
            if (state->board[row + 1][column + 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endTileColor = state->board[row + 1][column + 1]->GetColor();
                if (startPawnColor == endTileColor) {
                }
                // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
                if (startPawnColor != endTileColor) {
                    if (column < 6)
                        moveList.push_back(Move(*tile, Tile(row + 1, column + 1)));
                    else
                        AddSoldierUpgrade(&Move(*tile, Tile(row + 1, column + 1)), moveList, state);
                }
            }
        }
        if (row - 1 >= 0) {
            if (state->board[row - 1][column + 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endTileColor = state->board[row - 1][column + 1]->GetColor();
                if (startPawnColor == endTileColor) {
                }
                // jos vastustajan nappula niin lis�t��n moveListan
                if (startPawnColor != endTileColor) {
                    if (column < 6)
                        moveList.push_back(Move(*tile, Tile(row - 1, column + 1)));
                    else
                        AddSoldierUpgrade(&Move(*tile, Tile(row - 1, column + 1)), moveList, state);
                }
            }
        }
    }
    // perusruudut mustille 
    if ((column == 5 || column == 4 || column == 3 || column == 2 || column == 1) && startPawnColor == 1) {
        //siirtym�t eteenp�in
        if (state->board[row][column - 1] == NULL) {
            if (column > 1)
                moveList.push_back(Move(*tile, Tile(row, column - 1)));
            else
                AddSoldierUpgrade(&Move(*tile, Tile(row, column - 1)), moveList, state);
        }
        //sy�nnit viistoon
        if (row + 1 < 8) { // tarkastetaan ett� pysyt��n laudalla
            if (state->board[row + 1][column - 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endTileColor = state->board[row + 1][column - 1]->GetColor();
                if (startPawnColor == endTileColor) {
                }
                // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
                if (startPawnColor != endTileColor) {
                    if (column > 1)
                        moveList.push_back(Move(*tile, Tile(row + 1, column - 1)));
                    else
                        AddSoldierUpgrade(&Move(*tile, Tile(row + 1, column - 1)), moveList, state);
                }
            }
        }
        if (row - 1 >= 0) {
            if (state->board[row - 1][column - 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endTileColor = state->board[row - 1][column - 1]->GetColor();
                if (startPawnColor == endTileColor) {
                }
                // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
                if (startPawnColor != endTileColor) {
                    if (column > 1)
                        moveList.push_back(Move(*tile, Tile(row - 1, column - 1)));
                    else
                        AddSoldierUpgrade(&Move(*tile, Tile(row - 1, column - 1)), moveList, state);
                }
            }
        }
    }

    // Ohestaly�nti on mahdollinen, jos jollain sarakkeella on viimeksi
    // tapahtunut sotilaan kaksoisaskel.
    if (state->doublestepOnCol != -1)
    {
        if (color == 0 && column == 4)
        {
            if (state->board[state->doublestepOnCol][4] && state->board[state->doublestepOnCol][4]->GetCode() == PAWN)
                moveList.push_back(Move(*tile, Tile(state->doublestepOnCol, 5)));
        }
        if (color == 1 && column == 3)
        {
            if (state->board[state->doublestepOnCol][3] && state->board[state->doublestepOnCol][3]->GetCode() == PAWN)
                moveList.push_back(Move(*tile, Tile(state->doublestepOnCol, 2)));
        }
    }
}

//Palauttaa True jos tile on Ok eli ei uhattu
bool LegalMoves::IsTileCucked(Tile* tile, State* state, int opponentColor) {
    std::list<Move> opponentMoves;
    //Väreittäin käydään läpi kaikki ruudut ja niissä olevan nappulan siirrot kerätään vastustajan movemoveListan
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == NULL) continue;

            switch (state->board[i][j]->GetCode())
            {
            case KING:
                this->GetKingLegalMoves(opponentMoves, &Tile(i, j), state, opponentColor);
                break;
            case QUEEN:
                this->GetQueenLegalMoves(opponentMoves, &Tile(i, j), state, opponentColor);
                break;
            case ROOK:
                this->GetRookLegalMoves(opponentMoves, &Tile(i, j), state, opponentColor);
                break;
            case BISHOP:
                this->GetBishopLegalMoves(opponentMoves, &Tile(i, j), state, opponentColor);
                break;
            case KNIGHT:
                this->GetKnightLegal(opponentMoves, &Tile(i, j), state, opponentColor);
                break;
            case PAWN:
                this->GetSoldierLegalMoves(opponentMoves, &Tile(i, j), state, opponentColor);
                break;
            }
        }
    }

    // Käydöön vastustajaMoveLista löpi ja jos sieltö läytyy tarkasteltava tile niin tiedetöön sen olevan uhattu
    for (auto move : opponentMoves)
        if (tile->column == move.End().column && tile->row == move.End().row)
            return false;

    return true;
}

void LegalMoves::GetChecks(std::list<Move>& moveList, State* state, int color) {
    // käydään saatua movemoveLista läpi ja jos siellä oleva move asettaa kuninkaan shakkiin, niin move poistetaan moveListsta



    // Jotta ei jouduta perumaan oikeaan statean tehty� movea
    State testState;
    std::list<Move> cleanedMoves;
    for (auto s : moveList) {
        testState = *state;
        testState.UpdateState(&s);
        int x, y;

        // Kuninkaan move?
        if (s.IsShortCastle())
        {
            x = 6;
            if (state->GetTurn() == 0)
                y = 0;
            else
                y = 7;
        }
        else if (s.IsLongCastle())
        {
            x = 2;
            if (state->GetTurn() == 0)
                y = 0;
            else
                y = 7;
        }
        else
        {
            Pawn* moving = state->board[s.Start().column][s.Start().row];
            if (moving->GetCode() == KING)
            {
                x = s.End().column;
                y = s.End().row;
            }
            else
            {
                for (int i = 0; i < BOARD_SIZE; i++)
                    for (int j = 0; j < BOARD_SIZE; j++)
                        if (state->board[i][j]->GetCode() == KING)
                        {
                            x = i;
                            y = j;
                            break;
                        }
            }
        }


        // huom !color
        if (this->IsTileCucked(&Tile(x, y), &testState, !color))
            cleanedMoves.push_back(s);
    }

    moveList = cleanedMoves;
}
void LegalMoves::GetLegalMoves(State* state, std::list<Move>& moveList) {
    int color = state->GetTurn();

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (state->board[i][j] == NULL) continue;

            switch (state->board[i][j]->GetCode())
            {
            case KING:
                this->GetKingLegalMoves(moveList, &Tile(i, j), state, color);
                break;
            case QUEEN:
                this->GetQueenLegalMoves(moveList, &Tile(i, j), state, color);
                break;
            case ROOK:
                this->GetRookLegalMoves(moveList, &Tile(i, j), state, color);
                break;
            case BISHOP:
                this->GetBishopLegalMoves(moveList, &Tile(i, j), state, color);
                break;
            case KNIGHT:
                this->GetKnightLegal(moveList, &Tile(i, j), state, color);
                break;
            case PAWN:
                this->GetSoldierLegalMoves(moveList, &Tile(i, j), state, color);
                break;
            }
        }
    }

    GetCastleMoves(moveList, state, color);
    GetChecks(moveList, state, color);
}

void LegalMoves::AddSoldierUpgrade(Move* move, std::list<Move>& moveList, State* state) {
    if (move->End().row == 7) {
        // valkea korottaa
        move->_upgrade = state->wq;
        moveList.push_back(*move);

        Move rook = *move;
        rook._upgrade = state->wt;
        moveList.push_back(rook);

        Move bishop = *move;
        bishop._upgrade = state->wb;
        moveList.push_back(bishop);

        Move knight = *move;
        knight._upgrade = state->wh;
        moveList.push_back(knight);
    }
    else if (move->End().row == 0) {
        // musta korottaa
        move->_upgrade = state->bq;
        moveList.push_back(*move);

        Move rook = *move;
        rook._upgrade = state->bt;
        moveList.push_back(rook);

        Move bishop = *move;
        bishop._upgrade = state->bb;
        moveList.push_back(bishop);

        Move knight = *move;
        knight._upgrade = state->bh;
        moveList.push_back(knight);
    }
}