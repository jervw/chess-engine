#pragma once
#include "move.hh"

// luokka, jonka avulla saadaan palautettua minmax:ssa sek� move-olio ett� evaluointifunktion arvo
// Struct ajaisi saman asian. Kun ei rakenneta gettereit� ja settereit�, niin ei tarvita toteutus .cpp tiedostoa
class MinMax {
public:
    double _evalValue;
    Move _bestMove;
};
