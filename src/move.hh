#pragma once
#include "tile.hh"

class Nappula;

class Move
{
public:
    Move(Tile, Tile);
    Move() {}
    Move(bool, bool); // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi?
    Tile GetStartTile();
    Tile GetEndTile();
    bool IsShortCastle();
    bool IsLongCastle();
    Nappula* _miksikorotetaan = 0;

private:
    Tile _startTile;
    Tile _endTile;
    bool _shortCastle;
    bool _longCastle;
};