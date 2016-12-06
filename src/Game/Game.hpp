#ifndef GAME_H
#define GAME_H
#include "../RenderEngine/Display.hpp"

using namespace std;
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
