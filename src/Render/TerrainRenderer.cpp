#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "TerrainRenderer.hpp"

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

}

void TerrainRenderer::UnBindTerrain(Terrain& terrain)
{

}

void TerrainRenderer::RenderTerrain(Terrain& terrain)
{

}
