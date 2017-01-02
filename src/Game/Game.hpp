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
    double life;  // ranging between 0 and 10
    int gameState;  // states: start, running, over
    bool isTimeFrozen;  // press space to freeze the clock
    void BuildWorld(Loader& loader, vector<Entity>& entities, Terrain& theTerrain, vector<RawModel *>& rawModels);
    void ReplenishEnergy(double deltaEnergy = DELTA_ENERGY);
    void ConsumeEnergy(double deltaEnergy = DELTA_ENERGY);
    string StatusBar(int day, int hour);
};

#endif
