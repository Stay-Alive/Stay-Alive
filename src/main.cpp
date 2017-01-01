#include "Game/Game.hpp"

int main()
{
    Game game;
    while (true)  // use a dead loop so that we can replay after death
    {
        game.Start();
    }
    return 0;
}
