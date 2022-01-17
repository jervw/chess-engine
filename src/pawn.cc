#include <list>
#include <string>
#include "state.hh"
#include "pawn.hh"


Pawn::Pawn(std::wstring unicode, int color, int code)
{
    _unicode = unicode;
    _color = color;
    _code = code;
}


void Tower::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{

}


void Knight::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{

}


void Bishop::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{

}


void Queen::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{

}


void King::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{
    /*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
    oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

    Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/



}


void Soldier::GetMoves(std::list<Move>& moveList, Tile* tile, State* state, int color)
{

}


void Soldier::UpgradeSoldier(Move* move, std::list<Move>& moveList, State* state) {

}


