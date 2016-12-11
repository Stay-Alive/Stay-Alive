#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ModelTexture
{
public:
    ModelTexture();
    //@TODO
private:
    GLuint textureID;
    bool hasTransparency;
    bool useUpNormal;
    float shineDamper;
    float shine;
};

#endif
