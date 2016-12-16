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
    void LoadTransformMatrix(const glm::mat4& matrix);
    void LoadProjectionMatrix(const glm::mat4& matrix);
    void LoadViewMatrix(const glm::mat4& matrix);
    void LoadLight(const SimpleLight& light, GLfloat ambientLight);
    void LoadShineVariables(GLfloat shineDamper, GLfloat shine);
    void LoadUseUpNormal(bool useUpNormal);
private:
    GLuint transformMatrixLoc;
    GLuint projectionMatrixLoc;
    GLuint viewMatrixLoc;
    GLuint lightPositionLoc;
    GLuint useUpNormalLoc;
    GLuint lightColorLoc;
    GLuint ambientLightLoc;
    GLuint shineDamperLoc;
    GLuint shineLoc;
};

#endif
