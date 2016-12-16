#ifndef GAME_H
#define GAME_H
#include "../Render/Display.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Start();
private:
    Display *display;
};

#endif
