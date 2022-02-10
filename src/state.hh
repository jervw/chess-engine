#pragma once

#include <list>
#include <string>

#include "minmax.hh"
#include "move.hh"

#define BOARD_SIZE 8

// Ns. "forward declaration". Nyt State-luokassa voidaa esitell�
// Nappula-osoittimia ilman, ett� nappula.h -tiedostoa t�ytyy includoida.
class Pawn;

// State sis�lt�� kaiken tarvittavan informaation pelitilanteen kuvaamiseksi
// (nappuloiden sijainti, movevuoro, linnoitusoikeudet jne.).
class State {
public:
    // Peliboard sis�lt�� osoittimet kunkin ruudun nappula-olioon
    // (nullptr/NULL/0 jos tile on tyhj�). Public-m��reell�, koska t�t�
    // k�ytet��n paljon muualla.
    Pawn* board[BOARD_SIZE][BOARD_SIZE];

    // Nappula-oliot. Huomaa, ett� samaa nappulaa voidaan k�ytt�� useissa eri
    // ruuduissa. M��ritelty static-m��reell�, joten nappulat ovat kaikkien
    // board-olioiden "yhteisk�yt�ss�" (suorituskyvyn vuoksi).
    static Pawn* wk, * wq, * wt, * wb, * wh, * ws;  // Valkeat nappulat.
    static Pawn* bk, * bq, * bt, * bb, * bh, * bs;  // Mustat nappulat.

    // Ohestaly�nti� varten (-1 = sotilaan kaksoisaskelta ei tapahtunut
    // edellisell� siirrolla).
    int doublestepOnCol = -1;

    State();                      // Asettaa alkustaten.
    void UpdateState(Move*);      // P�ivitt�� staten annetulla siirrolla.
    double Evaluate();            // Staten numeerinen arviointi.
    MinMax Max(int depth);        // Minimax (max:n movevuoro).
    MinMax Min(int depth);        // Minimax (min:n movevuoro).
    MinMax GetMinMax(int depth);  // Minimax-algoritmi.
    void GetLegalMoves(std::list<Move>& moveList);  // Movegeneraattori.
    int GetTurn();                                  // Palauttaa movevuoron.
    void GetTurn(int);                              // Asettaa movevuoron.

    bool wKingMoved;
    bool wQRookMoved;
    bool wKRookMoved;


    bool bKingMoved;
    bool bQRookMoved;
    bool bKRookMoved;

private:
    int _turn;

    double CalculatePawnValues(int);
    bool IsOpeningOrMiddle(int);
    double PawnsMiddle(int);
    double Lines(int);
    bool TileAtRisk(Tile*, int opponentColor);
    void GetCastleMoves(std::list<Move>& moveList, int color);

    // Karsii siirrot, jotka j�tt�v�t oman K:n shakkiin.
    void WatchTileKingCheck(std::list<Move>& moveList, int color);
};