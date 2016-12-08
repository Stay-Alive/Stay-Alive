#ifndef RAWMODEL_H
#define RAWMODEL_H
#include <GLFW/glfw3.h>
#include <GL/glew.h>

class RawModel
{
public:
    RawModel(GLuint vaoID, int verticesNum): vaoID(vaoID), verticesNum(verticesNum) {}
    
    inline GLuint GetVaoID()
    {
        return vaoID;
    }

    inline int GetVerticeNum()
    {
        return verticesNum;
    }

private:
    GLuint vaoID;
    GLuint verticesNum;
};

#endif
