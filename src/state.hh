#pragma once

#include <list>
#include <string>
#include "minmax.hh"
#include "move.hh"


// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell� Nappula-osoittimia ilman,
// ett� nappula.h -tiedostoa t�ytyy includoida.
class Pawn;


// Asema sis�lt�� kaiken tarvittavan informaation pelitilanteen kuvaamiseksi
// (nappuloiden sijainti, siirtovuoro, linnoitusoikeudet jne.).
class State
{

public:
    // Pelilauta sis�lt�� osoittimet kunkin ruudun nappula-olioon (nullptr/NULL/0 jos ruutu on tyhj�).
    // Public-m��reell�, koska t�t� k�ytet��n paljon muualla.
    Pawn* board[8][8];

    // Nappula-oliot. Huomaa, ett� samaa nappulaa voidaan k�ytt�� useissa eri ruuduissa.
    // M��ritelty static-m��reell�, joten nappulat ovat kaikkien lauta-olioiden "yhteisk�yt�ss�"
    // (suorituskyvyn vuoksi).
    static Pawn* wk, * wq, * wt, * wb, * wh, * ws;	// Valkeat nappulat.
    static Pawn* bk, * bq, * bt, * bb, * bh, * bs;	// Mustat nappulat.

    // Ohestaly�nti� varten (-1 = sotilaan kaksoisaskelta ei tapahtunut edellisell� siirrolla).
    int kaksoisaskelSarakkeella = -1;

    State();												// Asettaa alkuaseman.
    void UpdateState(Move*);								// P�ivitt�� aseman annetulla siirrolla.
    double Evaluate();										// Aseman numeerinen arviointi.
    MinMax Max(int depth);							// Minimax (max:n siirtovuoro).
    MinMax Min(int depth);							// Minimax (min:n siirtovuoro).
    MinMax GetMinMax(int depth);						// Minimax-algoritmi.
    void GetLegalMoves(std::list<Move>& moveList);	// Siirtogeneraattori.
    int GetTurn();									// Palauttaa siirtovuoron.
    void GetTurn(int);								// Asettaa siirtovuoron.
    bool GetWKingState();					// Linnoittuminen mahdollista?
    bool GetBKingState();					// Linnoittuminen mahdollista?

private:

    double CalculatePawnValues(int);
    bool IsOpeningOrMiddle(int);
    double PawnsMiddle(int);
    double Lines(int);
    bool TileAtRisk(Tile*, int opponentColor);
    void GetCastleMoves(std::list<Move>& moveList, int color);

    // Karsii siirrot, jotka j�tt�v�t oman K:n shakkiin.
    void WatchKingCheck(std::list<Move>& moveList, int color);
};