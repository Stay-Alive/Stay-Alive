#include <iostream>
#include <vector>
#include <new>
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

    const char *text = str.c_str();
    int len = str.length();
    GLfloat *data = new GLfloat[len * 4 * 6];  // components: 4
    GLfloat marginX, fontSize, marginY;
    fontSize = FONT_SIZE;
    marginX = fontSize / 2;
    marginY = WINDOW_HEIGHT - fontSize;
    for (int i = 0; i < len; i++)
    {
        MakeCharacter(data+i*24, marginX, marginY, fontSize/2, fontSize, text[i]);
        marginX += fontSize;
    }
    GLuint buffer = GenerateFaces(4, len, data);
    delete [] data;
    // draw text
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const GLuint position = 0, uv = 1;
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(position);  // position
    glEnableVertexAttribArray(uv);  // uv
    glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 4, 0);
    glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE,
        sizeof(GLfloat) * 4, (GLvoid *)(sizeof(GLfloat) * 2));
    glDrawArrays(GL_TRIANGLES, 0, len * 6);
    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(uv);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisable(GL_BLEND);
    glDeleteBuffers(1, &buffer);
    glUseProgram(0);  // unuse
}

void TextRenderer::MakeCharacter(GLfloat *data, GLfloat x, GLfloat y, GLfloat n, GLfloat m, char c)
{
    GLfloat *d = data;
    GLfloat s = 0.0625;
    GLfloat a = s;
    GLfloat b = s * 2;
    int w = c - 32;
    GLfloat du = (w % 16) * a;
    GLfloat dv = 1 - (w / 16) * b - b;
    *(d++) = x - n; *(d++) = y - m;
    *(d++) = du + 0; *(d++) = dv;
    *(d++) = x + n; *(d++) = y - m;
    *(d++) = du + a; *(d++) = dv;
    *(d++) = x + n; *(d++) = y + m;
    *(d++) = du + a; *(d++) = dv + b;
    *(d++) = x - n; *(d++) = y - m;
    *(d++) = du + 0; *(d++) = dv;
    *(d++) = x + n; *(d++) = y + m;
    *(d++) = du + a; *(d++) = dv + b;
    *(d++) = x - n; *(d++) = y + m;
    *(d++) = du + 0; *(d++) = dv + b;
}

GLuint TextRenderer::GenerateFaces(int components, int len, GLfloat *data)
{
    GLuint buffer;
    int size = sizeof(GLfloat) * components * len * 6;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buffer;
}