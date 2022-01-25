#pragma once

#include <list>
#include <string>
#include <map>
#include "state.hh"
#include "move.hh"

// Vakioarvot nappulatyypeille.
enum PawnTypes
{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
};

enum Color
{
    WHITE, BLACK
};


// Yliluokka shakkinappuloille.
class Pawn
{

private:
    char _letter;
    int _color;		// valkea = 0, musta = 1
    int _code;		// VT, VR, MT tms.

public:
    Pawn(char, int, int);
    Pawn() {}

    // Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat t�m�n
    // omalla tavallaan.
    virtual void GetMoves(std::list<Move>& moveList, Tile*, State*, int color) = 0;

    void SetUnicode(char letter) { _letter = letter; }
    char GetLetter() { return _letter; }
    void SetColor(int color) { _color = color; }
    int GetColor() { return _color; }
    int GetCode() { return _code; }
    void SetCode(int code) { _code = code; }
};

// Torni-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Rook : public virtual Pawn {
public:
    Rook(char letter, int color, int code) : Pawn(letter, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Ratsu-aliluokka.
class Knight : public Pawn {
public:
    Knight(char letter, int color, int code) : Pawn(letter, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// L�hetti-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Bishop : public virtual Pawn {
public:
    Bishop(char letter, int color, int code) : Pawn(letter, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Daami-aliluokka. Perii sek� l�hetin ett� tornin.
class Queen : public Bishop, public Rook {
public:
    Queen(char letter, int color, int code) :
        Pawn(letter, color, code), Bishop(letter, color, code), Rook(letter, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Kuningas-aliluokka.
class King : public Pawn {
public:
    King(char letter, int color, int code) : Pawn(letter, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Sotilas-aliluokka.
class Soldier : public Pawn {
public:
    Soldier(char letter, int color, int code) : Pawn(letter, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
private:
    void UpgradeSoldier(Move*, std::list<Move>& moveList, State*);
};


