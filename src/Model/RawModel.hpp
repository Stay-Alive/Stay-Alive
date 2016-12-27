#ifndef RAWMODEL_H
#define RAWMODEL_H
#include <GL/glew.h>

class RawModel
{
public:
    RawModel() {}
    RawModel(GLuint vaoID, int verticesNum): vaoID(vaoID), verticesNum(verticesNum) {}
    ~RawModel() {}

    inline GLuint GetVaoID() const
    {
        return vaoID;
    }

    inline int GetVerticesNum() const
    {
        return verticesNum;
    }

private:
    GLuint vaoID;
    GLuint verticesNum;
};

#endif
