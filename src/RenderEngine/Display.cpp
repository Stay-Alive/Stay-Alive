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
	title = WINDOW_TITLE;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Needed to enable multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), NULL, NULL);
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
	const static int SAMPLE_SIZE = 512;
	static double samples[SAMPLE_SIZE] = {0.0};
	double avgTime = 0.0;
	static double previousTime = 0.0;
	double currentTime;
	int i;
	currentTime = glfwGetTime();

	for (i = 0; i < SAMPLE_SIZE - 1; i++)
	{
		samples[i] = samples[i+1];
		avgTime += samples[i];
	}
	samples[i] = currentTime - previousTime;
	previousTime = currentTime;
	avgTime += samples[i];
    avgTime /= SAMPLE_SIZE;
	glfwSetWindowTitle(window, (" | FPS: " + to_string(1.0 / avgTime)).c_str());
}
