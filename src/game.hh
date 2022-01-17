#pragma once

// Peli tietokonetta vastaan joko mustilla tai valkeilla.
class Game
{
public:
    Game(int);
    int GetEngineColor();

private:
    int _engineColor; // Valkoinen = 0, Musta = 1
};
