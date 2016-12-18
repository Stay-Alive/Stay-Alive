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

    /*
    vector<Entity> entities;

    int i, x, z;
    glm::vec3 noScale = glm::vec3(1, 1, 1);
    glm::vec3 noRotation = glm::vec3(0, 0, 0);

    // low poly tree
    RawModel mTree = ObjLoader::LoadModel("lowPolyTree", loader);
    ModelTexture mtTree(loader.LoadTexture("lowPolyTree"));
    TexturedModel tmTree(mTree, mtTree);
    for (i = 0; i < 25; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        entities.push_back(Entity(tmTree, glm::vec3(x, 0, z), noRotation, noScale));
    }

    // grass
    RawModel mGrass = ObjLoader::LoadModel("grass", loader);
    ModelTexture mtGrass(loader.LoadTexture("grass"), true, true);
    TexturedModel tmGrass(mGrass, mtGrass);
    for (i = 0; i < 25; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        entities.push_back(Entity(tmGrass, glm::vec3(x, 0, z), noRotation, noScale));
    }

    // fern, we have 4 types of textures
    RawModel mFern = ObjLoader::LoadModel("fern", loader);
    ModelTexture mtFern1(loader.LoadTexture("fern1"), true, true);
    ModelTexture mtFern2(loader.LoadTexture("fern2"), true, true);
    ModelTexture mtFern3(loader.LoadTexture("fern3"), true, true);
    ModelTexture mtFern4(loader.LoadTexture("fern4"), true, true);
    TexturedModel tmFern1(mFern, mtFern1);
    TexturedModel tmFern2(mFern, mtFern2);
    TexturedModel tmFern3(mFern, mtFern3);
    TexturedModel tmFern4(mFern, mtFern4);
    for (i = 0; i < 20; i++)
    {
        x = rand() % 200 - 100;
        z = rand() % 200 - 100;
        entities.push_back(Entity(i < 5 ? tmFern1 : i < 10 ? tmFern2 : i < 15 ? tmFern3 : tmFern4, glm::vec3 (x, 0, z), noRotation, noScale));
    }
    */

    vector<Terrain> terrains;
    ModelTexture mtGrass2(loader.LoadTexture("grassy2"), true);
    //ModelTexture mtGrass3(loader.LoadTexture("grassy3"), true);
    terrains.push_back(Terrain(-1, 0, loader, mtGrass2));
    terrains.push_back(Terrain(0, 0, loader, mtGrass2));
    terrains.push_back(Terrain(-1, -1, loader, mtGrass2));
    terrains.push_back(Terrain(0, -1, loader, mtGrass2));

    glm::vec3 colorWhite(1.0, 1.0, 1.0);
    glm::vec3 lightPosition(0.0, 50.0, 0.0);
    SimpleLight light(lightPosition, colorWhite);

    Camera camera;
    // @TODO render
    Renderer renderer(display->GetAspect());
/*
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //glLogicOp(GL_INVERT); // so that we can use xor to draw a photo
    //glEnable(GL_COLOR_LOGIC_OP);  // @ST seems not useful

#if TUTORIAL
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    string shadersPath = SHADERS_DIR;
    string vertexShaderPath = shadersPath + "SimpleVertexShader.vertexshader";
    string fragementShaderPath = shadersPath + "SimpleFragmentShader.fragmentshader";
	GLuint programID = LoadShaders(vertexShaderPath.c_str(), fragementShaderPath.c_str());

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
#endif

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
*/

    while(!display->IsWindowClosed())
    {
/*
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if TUTORIAL
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
#endif
*/

        camera.Update();

        for (Terrain& i: terrains)
        {
            renderer.AddTerrain(i);
        }
        // @TODO entities
        renderer.Render(light, camera);
#if 0
        cerr << "location: "<< camera.GetPosition().x << ", " << camera.GetPosition().y <<", " << camera.GetPosition().z << endl;
        //cerr << "view: "<< camera.GetViewDirection().x << ", " << camera.GetViewDirection().y <<", " << camera.GetViewDirection().z << endl;
#endif
        display->Update();
        display->ShowFPS();
    }
}
