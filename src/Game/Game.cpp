#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Game.hpp"
#include "../config.hpp"
#include "../RenderEngine/Display.hpp"
#include "../Shaders/shader.hpp"

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
    //glLogicOp(GL_INVERT);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while(!display->IsWindowClosed())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        display->Update();
        display->ShowFPS();
    }
}
