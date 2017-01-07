#ifndef RAWMODEL_H
#define RAWMODEL_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

class RawModel
{
public:
    RawModel() {}
    RawModel(GLuint vaoID, int verticesNum, vector<glm::vec3>& vertices): vaoID(vaoID), verticesNum(verticesNum), vertices(vertices) {}
    ~RawModel() {}

    inline GLuint GetVaoID() const
    {
        return vaoID;
    }

    inline int GetVerticesNum() const
    {
        return verticesNum;
    }

    inline const vector<glm::vec3>& GetVertices() const
    {
        return vertices;
    }

private:
    GLuint vaoID;
    GLuint verticesNum;
    vector<glm::vec3> vertices;
};

#endif
