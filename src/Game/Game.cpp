#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Game.hpp"
#include "../config.hpp"
#include "../RenderEngine/Display.hpp"

using namespace std;

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

    while(!display->IsWindowClosed())
    {
        display->Update();
        display->ShowFPS();
    }
}

Game::~Game()
{
    delete display;
    glfwTerminate();
}

void Game::Start()
{

	// Dark background
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glLogicOp(GL_INVERT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
