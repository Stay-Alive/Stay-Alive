#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.hpp"
#include "../Texture/ModelTexture.hpp"

class TexturedModel
{
public:
    TexturedModel(RawModel& rawModel, ModelTexture& texture, bool blendAlpha = false): rawModel(rawModel), texture(texture), blendAlpha(blendAlpha) {}

    inline RawModel GetRawModel() const
    {
        return rawModel;
    }

    inline ModelTexture GetTexture() const
    {
        return texture;
    }

    inline bool GetBlendAlpha() const
    {
        return blendAlpha;
    }

private:
    RawModel rawModel;
    ModelTexture texture;
    bool blendAlpha;
};

#endif
