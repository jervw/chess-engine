#pragma once
#include "tile.hh"

class Pawn;

class Move {
public:
    Move(Tile, Tile);
    Move() {}
    Move(bool, bool);  // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi?
    Tile Start();
    Tile End();
    bool IsShortCastle();
    bool IsLongCastle();
    Pawn* _upgrade = 0;

    bool operator== (const Move& rhs)
    {
        return _startTile == rhs._startTile && _endTile == rhs._endTile &&
            _shortCastle == rhs._shortCastle && _longCastle == rhs._longCastle;
    }

private:
    Tile _startTile;
    Tile _endTile;
    bool _shortCastle;
    bool _longCastle;
};