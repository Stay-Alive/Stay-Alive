#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

class Shader
{
public:
    static GLuint LoadShaders(string vertexFilePath, string fragmentFilePath);
};

#endif
