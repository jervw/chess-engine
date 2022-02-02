#include "move.hh"

Move::Move(Tile startTile, Tile endTile)
{
    _startTile = startTile;
    _endTile = endTile;
}


Move::Move(bool _shortCastle, bool _longCastle)
{

}

Tile Move::Start()
{
    return _startTile;
}


Tile Move::End()
{
    return _endTile;
}


bool Move::IsShortCastle()
{
    return _shortCastle;
}


bool Move::IsLongCastle()
{
    return _longCastle;
}
