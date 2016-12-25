#ifndef TERRAIN_SHADER_H
#define TERRAIN_SHADER_H
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Shader.hpp"

class TerrainShader: public Shader
{
public:
    TerrainShader();
    virtual ~TerrainShader();
    virtual void BindAttributes();
    virtual void GetUniformLocations();
    void LoadTransformMatrix(const glm::mat4& matrix);
    void LoadProjectionMatrix(const glm::mat4& matrix);
    void LoadViewMatrix(const glm::mat4& matrix);
    void LoadLight(const SimpleLight& light, GLfloat ambientLight);
    void LoadShineVariables(GLfloat shineDamper, GLfloat shine);
    void LoadTerrainSize(GLfloat terrainSize);
private:
    GLuint transformMatrixLoc;
    GLuint projectionMatrixLoc;
    GLuint viewMatrixLoc;
    GLuint lightPositionLoc;
    GLuint lightColorLoc;
    GLuint ambientLightLoc;
    GLuint shineDamperLoc;
    GLuint shineLoc;
    GLuint terrainSizeLoc;
};

#endif
