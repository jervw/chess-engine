#include <list>
#include <string>
#include "state.hh"
#include "pawn.hh"


Pawn::Pawn(char letter, int color, int code)
{
    _letter = letter;
    _color = color;
    _code = code;
}


void Rook::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
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


void Knight::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
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


void Bishop::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
    int row = tile->row;
    int column = tile->column;

    int startPawnColor, endPawnColor;


    startPawnColor = state->board[column][row]->GetColor();

    int j;
    // viistorivi ruudusta oikealle yl�s
    for (int i = column + 1; i < 8; i++) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == column + 1) {
            j = row + 1;
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
            endPawnColor = state->board[i][j]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }

        }
        j++;
    }

    // viistorivi ruudusta oikealle alas
    for (int i = column + 1; i < 8; i++) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == column + 1) {
            j = row - 1;
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
            endPawnColor = state->board[i][j]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }
        }

        j--;
    }

    // viistorivi ruudusta vasemmalle yl�s
    for (int i = column - 1; i >= 0; i--) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == column - 1) {
            j = row + 1;
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
            endPawnColor = state->board[i][j]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(i, j)));
                break;
            }
        }

        j++;
    }
    // viistorivi ruudusta vasemmalle alas
    for (int i = column - 1; i >= 0; i--) {
        // j arvo asetetaan vain silmukan ensimm�isell� kierroksella alkuarvoon
        if (i == column - 1) {
            j = row - 1;
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
            endPawnColor = state->board[i][j]->GetColor();
            if (startPawnColor == endPawnColor) {
                break;
            }
            // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
            if (startPawnColor != endPawnColor) {
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
    std::wcout << s.getAlkutile().column;
    std::wcout << s.getAlkutile().row << "-";

    std::wcout << s.getLopputile().column;
    std::wcout << s.getLopputile().row << "\n";
    }*/
}


void Queen::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
    this->Bishop::GetMoves(moveList, tile, state, color);
    this->Rook::GetMoves(moveList, tile, state, color);
    /*for (auto s : moveList)
    {
    std::wcout << L"Daami";
    std::wcout << s.getAlkutile().column;
    std::wcout << s.getAlkutile().row << "-";

    std::wcout << s.getLopputile().column;
    std::wcout << s.getLopputile().row << "\n";
    }*/

}


void King::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
    /*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
    oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

    Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/


    int row = tile->row;
    int column = tile->column;

    int startPawnColor;
    int endPawnColor;

    startPawnColor = state->board[column][row]->GetColor();


    // K�yd��n perussiirtojen tyhj�t ruudut l�pi 
    // Pit�� tarkistaa ett� ehdokas tile viel� laudalla
    if (column + 1 < 8) {
        if (state->board[column + 1][row] == NULL) {

            moveList.push_back(Move(*tile, Tile(column + 1, row)));


        }
        else if (state->board[column + 1][row] != NULL) {
            endPawnColor = state->board[column + 1][row]->GetColor();
            if (startPawnColor != endPawnColor) {
                moveList.push_back(Move(*tile, Tile(column + 1, row)));
            }


        }
    }

    if (column + 1 < 8 && row + 1 < 8) {
        if (state->board[column + 1][row + 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(column + 1, row + 1)));

        }
        else if (state->board[column + 1][row + 1] != NULL) {
            endPawnColor = state->board[column + 1][row + 1]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column + 1, row + 1)));

            }
        }
    }

    if (column + 1 < 8 && row - 1 >= 0) {
        if (state->board[column + 1][row - 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(column + 1, row - 1)));

        }
        else if (state->board[column + 1][row - 1] != NULL) {
            endPawnColor = state->board[column + 1][row - 1]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column + 1, row - 1)));

            }
        }
    }

    if (column - 1 >= 0) {
        if (state->board[column - 1][row] == NULL) {

            moveList.push_back(Move(*tile, Tile(column - 1, row)));

        }
        else if (state->board[column - 1][row] != NULL) {
            endPawnColor = state->board[column - 1][row]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column - 1, row)));

            }
        }
    }

    if (column - 1 >= 0 && row + 1 < 8) {
        if (state->board[column - 1][row + 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(column - 1, row + 1)));

        }
        else if (state->board[column - 1][row + 1] != NULL) {
            endPawnColor = state->board[column - 1][row + 1]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column - 1, row + 1)));

            }
        }
    }

    if (column - 1 >= 0 && row - 1 >= 0) {
        if (state->board[column - 1][row - 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(column - 1, row - 1)));

        }
        else if (state->board[column - 1][row - 1] != NULL) {
            endPawnColor = state->board[column - 1][row - 1]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column - 1, row - 1)));

            }
        }
    }

    if (row + 1 < 8) {
        if (state->board[column][row + 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(column, row + 1)));

        }
        else if (state->board[column][row + 1] != NULL) {
            endPawnColor = state->board[column][row + 1]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column, row + 1)));

            }
        }
    }

    if (row - 1 >= 0) {
        if (state->board[column][row - 1] == NULL) {

            moveList.push_back(Move(*tile, Tile(column, row - 1)));

        }
        else if (state->board[column][row - 1] != NULL) {
            endPawnColor = state->board[column][row - 1]->GetColor();
            if (startPawnColor != endPawnColor) {

                moveList.push_back(Move(*tile, Tile(column, row - 1)));

            }
        }
    }

}


void Soldier::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
    int row = tile->row;
    int column = tile->column;
    int startPawnColor;
    int endPawnColor;
    startPawnColor = state->board[column][row]->GetColor();

    // jos sotilas rivill� 2 ja sotilas valkea tai sotilas rivill� 7 ja sotilas musta sill� on kaksois askel mahdollisuus
    // muilla riveill� sotilaalla yks�is aske
    // sotilas voi my�s sy�d� etuviistoon ruudustaan
    // sotilas voi korottua jos se saavuttaa rivin 8 valkeilla ja vastaavasti rivin 1 mustilla

    // valkea rivill� 2
    if (row == 1 && startPawnColor == 0) {
        for (int i = row + 1; i < row + 3; i++) {
            // Jos tyhj� tile niin lis�t��n moveListan
            if (state->board[column][i] == NULL) {
                moveList.push_back(Move(*tile, Tile(column, i)));
            }
            else
                break;
        }
    }

    // musta rivill� 7
    if (row == 6 && startPawnColor == 1) {
        for (int i = row - 1; i > row - 3; i--) {
            // Jos tyhj� tile niin lis�t��n moveListan
            if (state->board[column][i] == NULL) {
                moveList.push_back(Move(*tile, Tile(column, i)));
            }
            else
                break;
        }
    }
    // perusruudut valkeille 
    if ((row == 2 || row == 3 || row == 4 || row == 5 || row == 6) && startPawnColor == 0) {
        //siirtym�t eteenp�in
        if (state->board[column][row + 1] == NULL) {
            if (row < 6)
                moveList.push_back(Move(*tile, Tile(column, row + 1)));
        }
        //sy�nnit viistoon
        if (column + 1 < 8) { // tarkastetaan ett� pysyt��n laudalla
            if (state->board[column + 1][row + 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endPawnColor = state->board[column + 1][row + 1]->GetColor();
                if (startPawnColor == endPawnColor) {
                }
                // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
                if (startPawnColor != endPawnColor) {
                    if (row < 6)
                        moveList.push_back(Move(*tile, Tile(column + 1, row + 1)));
                }
            }
        }
        if (column - 1 >= 0) {
            if (state->board[column - 1][row + 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endPawnColor = state->board[column - 1][row + 1]->GetColor();
                if (startPawnColor == endPawnColor) {
                }
                // jos vastustajan nappula niin lis�t��n moveListan
                if (startPawnColor != endPawnColor) {
                    if (row < 6)
                        moveList.push_back(Move(*tile, Tile(column - 1, row + 1)));
                }
            }
        }
    }
    // perusruudut mustille 
    if ((row == 5 || row == 4 || row == 3 || row == 2 || row == 1) && startPawnColor == 1) {
        //siirtym�t eteenp�in
        if (state->board[column][row - 1] == NULL) {
            if (row > 1)
                moveList.push_back(Move(*tile, Tile(column, row - 1)));
        }
        //sy�nnit viistoon
        if (column + 1 < 8) { // tarkastetaan ett� pysyt��n laudalla
            if (state->board[column + 1][row - 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endPawnColor = state->board[column + 1][row - 1]->GetColor();
                if (startPawnColor == endPawnColor) {
                }
                // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
                if (startPawnColor != endPawnColor) {
                    if (row > 1)
                        moveList.push_back(Move(*tile, Tile(column + 1, row - 1)));
                }
            }
        }
        if (column - 1 >= 0) {
            if (state->board[column - 1][row - 1] != NULL) {
                // Tarkistetaan ett� jos l�ht�ruudussa olevan nappulan v�ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
                endPawnColor = state->board[column - 1][row - 1]->GetColor();
                if (startPawnColor == endPawnColor) {
                }
                // jos vastujan nappula niin poistutaan for silmukasta. Lis�t��n moveListan
                if (startPawnColor != endPawnColor) {
                    if (row > 1)
                        moveList.push_back(Move(*tile, Tile(column - 1, row - 1)));
                }
            }
        }
    }

}


void Soldier::UpgradeSoldier(Move* move, std::list<Move>& moveList, State* state) {

}


