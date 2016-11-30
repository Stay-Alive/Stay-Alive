#include <stdio.h>
#include <stdlib.h>
#include "config.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef struct
{
    GLFWwindow *window;
} Model;
static Model model;
static Model *pModel = &model;

void CreateWindow();

int main()
{
	// Initialise window
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	pModel->window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT, "StayAlive", NULL, NULL);
	if (pModel->window == NULL)
    {
		fprintf(stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
	}

	// Open a window and create its OpenGL context
	glfwMakeContextCurrent(pModel->window);
    //glfwSwapInterval(VSYNC);
    glfwSetInputMode(pModel->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
    {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Dark background
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glLogicOp(GL_INVERT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// @TODO
	// load textures

    // load shaders

    int running = 1;
	while (running)
    {
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pModel->window);
		glfwPollEvents();

	}

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
