#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../config.hpp"
#include "EntityShader.hpp"

using namespace std;

EntityShader::EntityShader(): Shader("entity")
{
    BindAttributes();
    GetUniformLocations();
}

EntityShader::~EntityShader()
{

}

void EntityShader::BindAttributes()
{
    glBindAttribLocation(programID, 0, "position");  // @NOTE layout in shader file
    glBindAttribLocation(programID, 1, "texCoords");
    glBindAttribLocation(programID, 2, "normal");
}

void EntityShader::GetUniformLocations()
{
    // @NOTE see shader file
    transformMatrixLoc = glGetUniformLocation(programID, "transformMatrix");
    projectionMatrixLoc = glGetUniformLocation(programID, "projectionMatrix");
    viewMatrixLoc = glGetUniformLocation(programID, "viewMatrix");
    lightPositionLoc = glGetUniformLocation(programID, "lightPosition");
    useUpNormalLoc = glGetUniformLocation(programID, "useUpNormal");
    lightColorLoc = glGetUniformLocation(programID, "lightColor");
    ambientLightLoc = glGetUniformLocation(programID, "ambientLight");
    shineDamperLoc = glGetUniformLocation(programID, "shineDamper");
    shineLoc = glGetUniformLocation(programID, "shine");
}

void EntityShader::LoadTransformMatrix(const glm::mat4& matrix)
{
	//void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    glUniformMatrix4fv(transformMatrixLoc, 1, false, &matrix[0][0]);
}

void EntityShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
    glUniformMatrix4fv(projectionMatrixLoc, 1, false, &matrix[0][0]);
}


void EntityShader::LoadViewMatrix(const glm::mat4& matrix)
{
    glUniformMatrix4fv(viewMatrixLoc, 1, false, &matrix[0][0]);
}

void EntityShader::LoadLight(const SimpleLight& light, GLfloat ambientLight)
{
    glm::vec3 pos(light.GetPosition());
    glm::vec3 color(light.GetColor());
    glUniform3f(lightPositionLoc, pos.x, pos.y, pos.z);
    glUniform3f(lightColorLoc, color.x, color.y, color.z);
    glUniform1f(ambientLightLoc, ambientLight);
}

void EntityShader::LoadShineVariables(GLfloat shineDamper, GLfloat shine)
{
    glUniform1f(shineDamperLoc, shineDamper);
    glUniform1f(shineLoc, shine);
}

void EntityShader::LoadUseUpNormal(bool useUpNormal)
{
    // @NOTE useUpNormal in shader program is a GLfloat type
    glUniform1f(useUpNormalLoc, useUpNormal ? 1.0 : 0.0);
}
