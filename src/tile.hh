#pragma once

// Shakkilaudan ruutu tietyss� (rivi, sarake) -koordinaatissa.
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
