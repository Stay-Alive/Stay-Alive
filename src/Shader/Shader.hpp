#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

class Shader
{
public:
    Shader(const string& fileName);
    ~Shader();
private:
    GLuint programID;
    GLuint vertShaderID;
    GLuint fragShaderID;
    GLuint LoadShader(const string& fileName, GLenum shaderType);
};

#endif
