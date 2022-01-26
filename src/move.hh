#pragma once
#include "tile.hh"

class Nappula;

class Move {
public:
    Move(Tile, Tile);
    Move() {}
    Move(bool, bool);  // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi?
    Tile Start();
    Tile End();
    bool IsShortCastle();
    bool IsLongCastle();
    Nappula* _upgrade = 0;

private:
    Tile _startTile;
    Tile _endTile;
    bool _shortCastle;
    bool _longCastle;
};