#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../config.hpp"
#include "EntityShader.hpp"

using namespace std;

EntityShader::EntityShader(): Shader(string(SHADERS_DIR) + "basicShader")
{
    BindAttributes();
    GetUniformLocations();
}

void EntityShader::BindAttributes()
{
    glBindAttribLocation(programID, 0, "position");  // @NOTE layout in shader file
    glBindAttribLocation(programID, 1, "texCoords");
    glBindAttribLocation(programID, 2, "normal");
}
