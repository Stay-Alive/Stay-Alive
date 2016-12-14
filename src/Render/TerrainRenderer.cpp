#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "../config.hpp"
#include "TerrainRenderer.hpp"
#include "../Terrain/Terrain.hpp"
#include "../Model/RawModel.hpp"

using namespace std;

TerrainRenderer::TerrainRenderer(const glm::mat4& projectionMatrix)
{
    shader.Use();
    shader.LoadProjectionMatrix(projectionMatrix);
    glUseProgram(0);
}

TerrainRenderer::~TerrainRenderer()
{

}

void TerrainRenderer::BindTerrain(Terrain& terrain)
{
    glBindVertexArray(terrain.GetModel().GetVaoID());
    // enable attributes
    for (GLuint i = 0; i < 3; i++)
    {
        glEnableVertexAttribArray(i);
    }
    // load shine variables
    ModelTexture texture = terrain.GetTexture();
    shader.LoadShineVariables(texture.GetShineDamper(), texture.GetShine());
    // bind texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());

}

void TerrainRenderer::UnBindTerrain(Terrain& terrain)
{
    for (GLuint i = 0; i < 3; i++)
    {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

void TerrainRenderer::Render(vector<Terrain> terrains)
{
    for (Terrain& i: terrains)
    {
        BindTerrain(i);
        RenderTerrain(i);
        UnBindTerrain(i);
    }
}

void TerrainRenderer::RenderTerrain(Terrain& terrain)
{
    glm::vec3 postion(terrain.GetX(), terrain.GetY(), terrain.GetZ());
    glm::mat4 transMatrix = glm::translate(postion);  // generate translation matrix
    shader.LoadTransformMatrix(transMatrix);
    glDrawElements(GL_TRIANGLES, terrain.GetModel().GetVerticesNum(), GL_UNSIGNED_INT, 0);  // 0 indicates the buffer offset in indices buffer object
}
