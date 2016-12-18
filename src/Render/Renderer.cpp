#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "../config.hpp"
#include "Renderer.hpp"

using namespace std;

Renderer::Renderer(GLfloat aspect): projectionMatrix(glm::perspective((GLfloat)FIELD_OF_VIEW, aspect, (GLfloat)Z_NEAR, (GLfloat)Z_FAR)), terrainRenderer(projectionMatrix), entityRenderer(projectionMatrix)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    // alpha blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // antialiasing
    glEnable(GL_MULTISAMPLE);
	// Dark background
	glClearColor(SKY_R, SKY_G, SKY_B, 1.0f);
}

Renderer::~Renderer()
{

}

void Renderer::AddTerrain(const Terrain& terrain)
{
    terrains.push_back(terrain);
}

void Renderer::AddEntity(const Entity& entity)
{
    const TexturedModel& texturedModel = entity.GetModel();
    // initialize value to an empty vector
    entities.insert(TmEntityMap::value_type(texturedModel, vector<Entity>()));
    entities[texturedModel].push_back(entity);
}

void Renderer::Render(const SimpleLight& light, const Camera& camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render terrains
    TerrainShader& terrainShader = terrainRenderer.GetShader();
    terrainShader.Use();
    terrainShader.LoadLight(light, 0.1);
    terrainShader.LoadViewMatrix(camera.GetViewMatrix());
    terrainRenderer.Render(terrains);
    glUseProgram(0);  // unuse
    terrains.clear();
    // render entities
    EntityShader& entityShader = entityRenderer.GetShader();
    entityShader.Use();
    entityShader.LoadLight(light, 0.1);
    entityShader.LoadViewMatrix(camera.GetViewMatrix());
    entityRenderer.Render(entities, camera.GetPosition());
    glUseProgram(0);  // unuse
    entities.clear();
}
