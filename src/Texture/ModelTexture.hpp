#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ModelTexture
{
public:
    ModelTexture(GLuint id, bool hasTransparency = false, bool useUpNormal = false, float shine = 0, float shineDamper = 1): textureID(id), hasTransparency(hasTransparency), useUpNormal(useUpNormal), shine(shine), shineDamper(shineDamper) {}

    inline GLuint GetTextureID() const
    {
        return textureID;
    }

    inline float GetShineDamper() const
    {
        return textureID;
    }

    inline void SetShineDamper(float shineDamper)
    {
        this->shineDamper = shineDamper;
    }

    inline float GetShine() const
    {
        return shine;
    }

    inline void SetShine(float shine)
    {
        this->shine = shine;
    }

    inline bool GetHasTransparency() const
    {
        return hasTransparency;
    }

    inline bool GetUseUpNormal()
    {
        return useUpNormal;
    }

private:
    GLuint textureID;
    bool hasTransparency;
    bool useUpNormal;
    float shine;
    float shineDamper;
};

#endif
