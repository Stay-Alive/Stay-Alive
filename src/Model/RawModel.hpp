#ifndef RAWMODEL_H
#define RAWMODEL_H
#include <GL/glew.h>

class RawModel
{
public:
    RawModel(GLuint vaoID, int verticesNum): vaoID(vaoID), verticesNum(verticesNum) {}

    inline GLuint GetVaoID()
    {
        return vaoID;
    }

    inline int GetVerticesNum()
    {
        return verticesNum;
    }

private:
    GLuint vaoID;
    GLuint verticesNum;
};

#endif
