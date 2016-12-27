#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <iostream>
#include <vector>
#include "../Shader/TextShader.hpp"
using namespace std;

class TextRenderer
{
public:
    TextRenderer(GLuint textureID);
    virtual ~TextRenderer();
    void Render(const string& str);
private:
    TextShader shader;
    GLuint textureID;
};

#endif
