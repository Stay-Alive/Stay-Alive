#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Light/Light.hpp"

using namespace std;

class Shader
{
public:
    Shader(const string& fileName);
    virtual ~Shader();
    virtual void BindAttributes() = 0;
    virtual void GetUniformLocations() = 0;
    void Use();
private:
    GLuint LoadShader(const string& fileName, GLenum shaderType);
protected:
    GLuint programID;
    GLuint vertShaderID;
    GLuint fragShaderID;
};

#endif
