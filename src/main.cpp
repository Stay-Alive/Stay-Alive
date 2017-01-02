#include "Game/Game.hpp"

int main()
{
    Game game;
    while (true)  // use a dead loop so that we can replay happily
    {
        game.Start();
    }
    return 0;
}
