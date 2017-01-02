#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <iostream>
#include <vector>
#include "../Shader/TextShader.hpp"
using namespace std;

class TextRenderer
{
public:
    TextRenderer(GLuint textureID);
    virtual ~TextRenderer();
    void Render(const string& str);
private:
    TextShader shader;
    GLuint textureID;
    void MakeCharacter(GLfloat *data, GLfloat marginX, GLfloat marginY, GLfloat fontWidth, GLfloat fontHeight, char c);
    GLuint GenerateFaces(int components, int len, GLfloat *data);
    void MatOrtho(float *matrix, float left, float right, float bottom, float top, float near, float far);
};

#endif
