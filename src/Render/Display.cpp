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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

void Display::ShowFPS(double timeInterval)
{
	static double previousTime = glfwGetTime();  // Set the initial time to now
	static int fpsFrameCount = 0;  // Set the initial FPS frame count to 0
	static double fps = 0.0;  // Set the initial FPS value to 0.0

	double currentTime = glfwGetTime();

	if (timeInterval < 0.1)
	{
		timeInterval = 0.1;
	}
	else if (timeInterval > 10.0)
	{
		timeInterval = 10.0;
	}
	// Calculate and display the FPS every specified time interval
	if ((currentTime - previousTime) > timeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - previousTime);
		// Update window title
	    glfwSetWindowTitle(window, (title + " | FPS: " + to_string(int(fps))).c_str());
		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		previousTime = glfwGetTime();
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}
}
