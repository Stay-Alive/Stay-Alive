#ifndef TEXTURE_MODEL_H
#define TEXTURE_MODEL_H

#include <glm/glm.hpp>
#include "RawModel.hpp"
#include "../Texture/ModelTexture.hpp"

class TexturedModel
{
public:
    TexturedModel() {} // @TODO
    inline RawModel GetRawModel() const { return rawModel; }
};

#endif
