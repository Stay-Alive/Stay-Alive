#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.hpp"
#include "../Texture/ModelTexture.hpp"

class TexturedModel
{
public:
    TexturedModel(RawModel& rawModel, ModelTexture& texture, bool blendAlpha = false): rawModelPtr(&rawModel), texture(texture), blendAlpha(blendAlpha) {}

    inline RawModel* GetRawModel() const
    {
        return rawModelPtr;
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
    RawModel* rawModelPtr;  // @NOTE this is a pointer now
    ModelTexture texture;
    bool blendAlpha;
};

#endif
