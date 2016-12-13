#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../Entity/Light.hpp"

using namespace std;

class Shader
{
public:
    Shader(const string& fileName);
    virtual ~Shader();
    virtual void BindAttributes() = 0;
    virtual void GetUniformLocations() = 0;
private:
    GLuint LoadShader(const string& fileName, GLenum shaderType);
protected:
    GLuint programID;
    GLuint vertShaderID;
    GLuint fragShaderID;
};

#endif
