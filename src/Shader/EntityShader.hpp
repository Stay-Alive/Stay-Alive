#ifndef ENTITY_SHADER_H
#define ENTITY_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class EntityShader: public Shader
{
public:
    EntityShader();
    virtual ~EntityShader();
    virtual void BindAttributes();
    virtual void GetUniformLocations();
};

#endif
