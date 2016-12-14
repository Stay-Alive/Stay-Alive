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

    inline float GetY() const
    {
        return y;
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
    const float SIZE = 800;  // @TODO we might move this const data to config.hpp
    const int VERTEX_COUNT = 128;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    ModelTexture texture;
    RawModel model;
    RawModel GenerateTerrain(Loader& loader);
};

#endif
