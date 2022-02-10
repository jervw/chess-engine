#pragma once
#include <string>
#include <list>
#include "pawn.hh"
#include "tile.hh"
#include "move.hh"
#include "state.hh"

class State;

class LegalMoves {
public:
    LegalMoves() {};
    void GetLegalMoves(State*, std::list<Move>& moveList);
    void GetRookLegalMoves(std::list<Move>& moveList, Tile*, State*, int color);
    void GetBishopLegalMoves(std::list<Move>& moveList, Tile*, State*, int color);
    void GetQueenLegalMoves(std::list<Move>& moveList, Tile*, State*, int color);
    void GetKingLegalMoves(std::list<Move>& moveList, Tile*, State*, int color);
    void GetKnightLegal(std::list<Move>& moveList, Tile*, State*, int color);
    void GetSoldierLegalMoves(std::list<Move>& moveLista, Tile*, State*, int color);
    void GetCastleMoves(std::list<Move>& moveList, State*, int color);
    void GetChecks(std::list<Move>& moveList, State*, int color); // poistaa moveListsta siirrot jotka viev�t kuninkaan shakkiin
    bool IsTileCucked(Tile*, State*, int opponentColor);
private:
    void AddSoldierUpgrade(Move*, std::list<Move>& moveList, State*);
};