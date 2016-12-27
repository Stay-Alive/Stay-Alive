#ifndef TEXT_H
#define TEXT_H

#include <GL/glew.h>
using namespace std;

class Text
{
public:
    Text(GLuint textureID);
    ~Text();
    void RenderText();
private:
    GLuint programID;
    GLuint textureID;
};

#endif
