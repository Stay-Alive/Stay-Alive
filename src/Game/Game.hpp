#ifndef GAME_H
#define GAME_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../config.hpp"
#include "../Render/Display.hpp"
#include "../Render/Loader.hpp"
#include "../Render/ObjLoader.hpp"
#include "../Render/Renderer.hpp"
#include "../Model/TexturedModel.hpp"
#include "../Model/RawModel.hpp"
#include "../Entity/Entity.hpp"
#include "../Terrain/Terrain.hpp"
#include "../Light/Light.hpp"
#include "../Entity/Camera.hpp"
#include "../Render/TextRenderer.hpp"
#include "../Light/ClockTime.hpp"
using namespace std;

class Game
{
public:
    Game();
    ~Game();
    void Start();
private:
    Display *display;
    double life;  // ranging between 0 and 1
    int day;
    int gameTime;  // ranging from 0 to 23 pm
    int gameState;  // states: start, running, over
    void BuildWorld(Loader& loader, vector<Entity>& entities, Terrain& theTerrain);
    string StatusBar();
};

#endif
