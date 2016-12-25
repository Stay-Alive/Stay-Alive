#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model/RawModel.hpp"
#include "../Texture/ModelTexture.hpp"
#include "../Render/Loader.hpp"

class Terrain
{
public:
    Terrain(Loader& loader, ModelTexture texture);

    virtual ~Terrain();

    inline float GetX() const
    {
        return x;
    }

    inline float GetY() const
    {
        return 0;
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
    GLfloat x;
    GLfloat y;
    GLfloat z;
    ModelTexture texture;
    RawModel model;
    RawModel GenerateTerrain(Loader& loader);
};

#endif
