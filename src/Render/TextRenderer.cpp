#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "../config.hpp"
#include "TextRenderer.hpp"

using namespace std;

TextRenderer::TextRenderer(GLuint textureID): textureID(textureID)
{

}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Render(const string& str)
{
    glm::mat4 matrix = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);
    shader.Use();
    shader.LoadMatrix(matrix);

    char *text = str.c_str();
    int length = str.length;
    GLfloat data[] = new GLfloat[length * 4 * 6];  // components: 4
    for (int i = 0; i < length; i++)
    {

    }
    delete [] data;
}
