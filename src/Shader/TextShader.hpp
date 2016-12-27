#ifndef TEXT_SHADER_H
#define TEXT_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Shader.hpp"

class TextShader: public Shader
{
public:
    TextShader();
    virtual ~TextShader();
    virtual void BindAttributes();
    virtual void GetUniformLocations();
    void LoadMatrix(const glm::mat4& matrix);

private:
    GLuint matrixLoc;
};

#endif
