#pragma once

// Shakkilaudan ruutu tietyssä (sarake, rivi ) -koordinaatissa.
class Tile {
public:
    Tile(int, int);
    Tile() {}
    int GetRow();
    int GetColumn();
    void SetRow(int);
    void SetColumn(int);

private:
    int _column;
    int _row;
};
