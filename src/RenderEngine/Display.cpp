#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../config.hpp"
#include "Display.hpp"

using namespace std;

Display::Display()
{
	// Set minimum OpenGL version and options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Needed to enable multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    aspect = WINDOW_WIDTH * 1.0 / WINDOW_HEIGHT;
    if (window == NULL)
    {
		cerr << "Failed to open GLFW window.\n" << endl;
		glfwTerminate();
	}
	// Open a window and create its OpenGL context
	glfwMakeContextCurrent(window);
	// Set OpenGL viewport to full size of the window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Enable vertical sync
    glfwSwapInterval(1);

}

Display::~Display()
{
	cerr << "Window destroyed\n";
	glfwDestroyWindow(window);
}

void Display::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Display::IsWindowClosed()
{
	return glfwWindowShouldClose(window);
}

double Display::GetAspect()
{
	return aspect;
}

void Display::ShowFPS()
{

}
