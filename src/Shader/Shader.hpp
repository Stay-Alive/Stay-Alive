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
    virtual ~Shader();
    virtual void BindAttributes();
    virtual void GetUniformLocations();
private:
    GLuint LoadShader(const string& fileName, GLenum shaderType);
protected:
    GLuint programID;
    GLuint vertShaderID;
    GLuint fragShaderID;
    GLuint viewMatrixLoc;
    // @TODO
};

#endif
