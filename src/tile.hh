#pragma once

// Shakkilaudan tile tietyssä (sarake, rivi ) -koordinaatissa.
class Tile {
public:
    Tile(int col, int row);
    Tile() {};
    bool operator== (const Tile& rhs) { return column == rhs.column && row == rhs.row; }
    int column, row;
};
