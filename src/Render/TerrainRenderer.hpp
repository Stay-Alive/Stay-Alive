#ifndef TERRAIN_RENENDER_H
#define TERRAIN_RENENDER_H

#include <iostream>
#include <vector>
#include "../Terrain/Terrain.hpp"
#include "../Shader/TerrainShader.hpp"

using namespace std;
class TerrainRenderer
{
public:
    TerrainRenderer(const glm::mat4& projectionMatrix);
    virtual ~TerrainRenderer();
    void Render(vector<Terrain> terrains);

    inline TerrainShader& GetShader()
    {
        return shader;
    }
private:
    TerrainShader shader;
    void BindTerrain(Terrain& terrain);
    void UnbindTerrain(Terrain& terrain);
    void RenderTerrain(Terrain& terrain);
};

#endif
