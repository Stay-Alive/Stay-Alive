#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model/RawModel.hpp"
#include "../Texture/ModelTexture.hpp"
#include "../Render/Loader.hpp"

class Terrain
{
public:
    Terrain(int gridX, int gridZ, Loader& loader, ModelTexture texture): x(gridX * SIZE), z(gridZ * SIZE), texture(texture), model(GenerateTerrain(loader)) {}

    virtual ~Terrain() {}

    inline float GetX() const
    {
        return x;
    }

    inline float GetZ() const
    {
        return z;
    }

    inline RawModel GetModel() const
    {
        return model;
    }

    inline ModelTexture GetTexture() const
    {
        return texture;
    }

private:
    const float SIZE = 800;
    const int VERTEX_COUNT = 128;
    float x;
    float z;
    ModelTexture texture;
    RawModel model;
    RawModel GenerateTerrain(Loader& loader);
};

#endif
