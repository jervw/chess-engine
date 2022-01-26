#pragma once

// Shakkilaudan ruutu tietyssä (sarake, rivi ) -koordinaatissa.
class Tile {
public:
    Tile(int col, int row) : column(col), row(row) {};
    Tile() {}
    int column, row;
};
