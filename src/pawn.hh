#pragma once

#include <list>
#include <string>
#include "state.hh"
#include "move.hh"

// Vakioarvot nappulatyypeille.
enum
{
    WT, WH, WB, WQ, WK, WS,
    BT, BH, BB, BQ, BK, BS
};

// Yliluokka shakkinappuloille.
class Pawn
{

private:
    std::wstring	_unicode;
    int				_color;		// valkea = 0, musta = 1
    int				_code;		// VT, VR, MT tms.

public:
    Pawn(std::wstring, int, int);
    Pawn() {}

    // Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat t�m�n
    // omalla tavallaan.
    virtual void GetMoves(std::list<Move>& moveList, Tile*, State*, int color) = 0;

    void SetUnicode(std::wstring unicode) { _unicode = unicode; }
    std::wstring GetUnicode() { return _unicode; }
    void SetColor(int color) { _color = color; }
    int GetColor() { return _color; }
    int GetCode() { return _code; }
    void SetCode(int code) { _code = code; }
};

// Torni-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Tower : public virtual Pawn {
public:
    Tower(std::wstring unicode, int color, int code) : Pawn(unicode, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Ratsu-aliluokka.
class Knight : public Pawn {
public:
    Knight(std::wstring unicode, int color, int code) : Pawn(unicode, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// L�hetti-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Bishop : public virtual Pawn {
public:
    Bishop(std::wstring unicode, int color, int code) : Pawn(unicode, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Daami-aliluokka. Perii sek� l�hetin ett� tornin.
class Queen : public Bishop, public Tower {
public:
    Queen(std::wstring unicode, int color, int code) :
        Pawn(unicode, color, code), Bishop(unicode, color, code), Tower(unicode, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Kuningas-aliluokka.
class King : public Pawn {
public:
    King(std::wstring unicode, int color, int code) : Pawn(unicode, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
};

// Sotilas-aliluokka.
class Soldier : public Pawn {
public:
    Soldier(std::wstring unicode, int color, int code) : Pawn(unicode, color, code) {}
    void GetMoves(std::list<Move>& moveList, Tile*, State*, int color);
private:
    void UpgradeSoldier(Move*, std::list<Move>& moveList, State*);
};


