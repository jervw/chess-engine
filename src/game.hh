#pragma once

// Peli tietokonetta vastaan joko mustilla tai valkeilla.
class Game
{
public:
    Game(int color);
    int GetHumanColor();
    int GetEngineColor();

private:
    int _humanColor;
    int _engineColor; // Valkoinen = 0, Musta = 1
};
