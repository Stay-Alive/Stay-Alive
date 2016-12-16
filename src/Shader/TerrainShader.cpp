#include "../config.hpp"
#include "TerrainShader.hpp"

TerrainShader::TerrainShader(): Shader("terrainShader")
{
    BindAttributes();
    GetUniformLocations();
}

TerrainShader::~TerrainShader()
{

}

void TerrainShader::BindAttributes()
{
    glBindAttribLocation(programID, 0, "position");  // @NOTE layout in shader file
    glBindAttribLocation(programID, 1, "texCoords");
    glBindAttribLocation(programID, 2, "normal");
}

void TerrainShader::GetUniformLocations()
{
    // @NOTE see shader file
    transformMatrixLoc = glGetUniformLocation(programID, "transformMatrix");
    projectionMatrixLoc = glGetUniformLocation(programID, "projectionMatrix");
    viewMatrixLoc = glGetUniformLocation(programID, "viewMatrix");
    lightPositionLoc = glGetUniformLocation(programID, "lightPosition");
    lightColorLoc = glGetUniformLocation(programID, "lightColor");
    ambientLightLoc = glGetUniformLocation(programID, "ambientLight");
    shineDamperLoc = glGetUniformLocation(programID, "shineDamper");
    shineLoc = glGetUniformLocation(programID, "shine");
}

void TerrainShader::LoadTransformMatrix(const glm::mat4& matrix)
{
	//void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    glUniformMatrix4fv(transformMatrixLoc, 1, false, &matrix[0][0]);
}

void TerrainShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
    glUniformMatrix4fv(projectionMatrixLoc, 1, false, &matrix[0][0]);
}


void TerrainShader::LoadViewMatrix(const glm::mat4& matrix)
{
    glUniformMatrix4fv(viewMatrixLoc, 1, false, &matrix[0][0]);
}

void TerrainShader::LoadLight(const SimpleLight& light, GLfloat ambientLight)
{
    glm::vec3 pos(light.GetPosition());
    glm::vec3 color(light.GetPosition());
    glUniform3f(lightPositionLoc, pos.x, pos.y, pos.z);
    glUniform3f(lightColorLoc, color.x, color.y, color.z);
    glUniform1f(ambientLightLoc, ambientLight);
}

void TerrainShader::LoadShineVariables(GLfloat shineDamper, GLfloat shine)
{
    glUniform1f(shineDamperLoc, shineDamper);
    glUniform1f(shineLoc, shine);
}
