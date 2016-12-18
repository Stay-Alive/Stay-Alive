#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../config.hpp"
#include "../Terrain/Terrain.hpp"
#include "../Entity/Entity.hpp"
#include "../Entity/Light.hpp"
#include "../Entity/Camera.hpp"
#include "../Shader/Shader.hpp"
#include "../Shader/EntityShader.hpp"
#include "../Shader/TerrainShader.hpp"
#include "TerrainRenderer.hpp"
#include "EntityRenderer.hpp"

using namespace std;

class Renderer
{
public:
    Renderer(GLfloat aspect = ASPECT);
    virtual ~Renderer();
    void Render(const SimpleLight& light, const Camera& camera);
    void AddTerrain(const Terrain& terrain);
    void AddEntity(const Entity& entity);
private:
    glm::mat4 projectionMatrix;
    TerrainRenderer terrainRenderer;
    EntityRenderer entityRenderer;
    vector<Terrain> terrains;
    TmEntityMap entities;
};

#endif
