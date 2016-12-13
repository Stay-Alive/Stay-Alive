#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
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
using namespace std;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void Render(const SimpleLight& light, const Camera& camera);
    void AddTerrain(const Terrain& terrain);
    void AddEntity(const Entity& entity);
private:
    glm::mat4 projectionMatrix;
    //EntityShader& entityShader;
    //TerrainShader terrainShader;
    //TerrainShader terrainShader;
    TerrainRenderer terrainRenderer;
    vector<Terrain> terrains;
};

#endif
