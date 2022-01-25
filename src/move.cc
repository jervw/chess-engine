#include "move.hh"

Move::Move(Tile startTile, Tile endTile)
{
    _startTile = startTile;
    _endTile = endTile;
}


Move::Move(bool _shortCastle, bool _longCastle)
{

}

Tile Move::GetStartTile()
{
    return _startTile;
}


Tile Move::GetEndTile()
{
    return _endTile;
}


bool Move::IsShortCastle()
{
    return 0;
}


bool Move::IsLongCastle()
{
    return 0;
}
