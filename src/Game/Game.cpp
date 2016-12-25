#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Game.hpp"
#include "../config.hpp"
#include "../Render/Display.hpp"
#include "../Render/Loader.hpp"
#include "../Render/ObjLoader.hpp"
#include "../Render/Renderer.hpp"
#include "../Model/TexturedModel.hpp"
#include "../Model/RawModel.hpp"
#include "../Entity/Entity.hpp"
#include "../Terrain/Terrain.hpp"
#include "../Entity/Light.hpp"
#include "../Entity/Camera.hpp"
using namespace std;

#define TUTORIAL 0

#if TUTORIAL
#include "../Shader/shader.hpp"
#endif

Game::Game()
{
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        return;
    }
    display = new Display();
    glewExperimental = GL_TRUE;
    // Initialize GLEW
	if (glewInit() != GLEW_OK)
    {
		cerr << "Failed to initialize GLEW\n";
	}
}

Game::~Game()
{
    delete display;
    glfwTerminate();
}

void Game::Start()
{
    cerr << "Game started\n";
    Loader loader;
    srand(time(NULL));  // initialize random number generation
    vector<Entity> entities;


    int i, x, z, rotateAngle;
    glm::vec3 standardScale = glm::vec3(1, 1, 1);
    glm::vec3 noRotation = glm::vec3(0, 0, 0);

    // low poly tree
    RawModel mTree = ObjLoader::LoadModel("lowPolyTree", loader);
    ModelTexture mtTree(loader.LoadTexture("lowPolyTree"));
    TexturedModel tmTree(mTree, mtTree);
    for (i = 0; i < 25; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmTree, glm::vec3(x, 0, z), glm::vec3(0, rotateAngle, 0), standardScale));
    }

    // grass
    RawModel mGrass = ObjLoader::LoadModel("grass", loader);
    ModelTexture mtGrass(loader.LoadTexture("grass"));
    TexturedModel tmGrass(mGrass, mtGrass);
    for (i = 0; i < 25; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmGrass, glm::vec3(x, 0, z), glm::vec3(0, rotateAngle, 0), standardScale));
    }

    // stall
    RawModel mStall = ObjLoader::LoadModel("stall", loader);
    ModelTexture mtStall(loader.LoadTexture("stall"));
    TexturedModel tmStall(mStall, mtStall);
    entities.push_back(Entity(tmStall, glm::vec3(x, 0, z), noRotation, standardScale * 1.5f));

    // box
    RawModel mBox = ObjLoader::LoadModel("box", loader);
    ModelTexture mtBox(loader.LoadTexture("box"));
    TexturedModel tmBox(mBox, mtBox);
    for (i = 0; i < 4; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmBox, glm::vec3(x, 0, z), glm::vec3(0, rotateAngle, 0), standardScale));
    }

    // fern, we have 4 types of textures
    RawModel mFern = ObjLoader::LoadModel("fern", loader);
    vector<TexturedModel> fernTexturedModels;
    ModelTexture mtFern1(loader.LoadTexture("fern1"));
    ModelTexture mtFern2(loader.LoadTexture("fern2"));
    ModelTexture mtFern3(loader.LoadTexture("fern3"));
    ModelTexture mtFern4(loader.LoadTexture("fern4"));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern1));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern2));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern3));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern4));
    for (i = 0; i < 20; i++)
    {
        x = rand() % 200 - 100;
        z = rand() % 200 - 100;
        int fernType = rand() % 4;
        entities.push_back(Entity(fernTexturedModels[fernType], glm::vec3 (x, 0, z), noRotation, standardScale * 0.5f));
    }

    vector<Terrain> terrains;
    ModelTexture mtGrass2(loader.LoadTexture("grassy2", true));
    terrains.push_back(Terrain(loader, mtGrass2));

    glm::vec3 colorWhite(1.0, 1.0, 1.0);
    glm::vec3 lightPosition(0.0, LIGHT_HEIGHT, 0.0);
    SimpleLight light(lightPosition, colorWhite);

    Camera camera;
    Renderer renderer(display->GetAspect());

    while(!display->IsWindowClosed())
    {

        camera.Update();
        // terrains
        for (Terrain& tmpTerrain: terrains)
        {
            renderer.AddTerrain(tmpTerrain);
        }
        // entities
        for (Entity& tmpEntity: entities)
        {
            renderer.AddEntity(tmpEntity);
        }
        renderer.Render(light, camera);
#if 0
        cerr << "location: "<< camera.GetPosition().x << ", " << camera.GetPosition().y <<", " << camera.GetPosition().z << endl;
        //cerr << "view: "<< camera.GetViewDirection().x << ", " << camera.GetViewDirection().y <<", " << camera.GetViewDirection().z << endl;
        //cerr << "Error: " << glGetError() << std::endl; // 返回 0 (无错误)
#endif
        display->Update();
        display->ShowFPS();
    }
}
