#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../config.hpp"
#include "Entity.hpp"

using namespace std;

Entity::Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): model(model), position(position), rotation(rotation), scale(scale)
{
    ComputeAABB(position, rotation);
}

void Entity::ComputeAABB(glm::vec3 position, glm::vec3 rotation)
{
    const vector<glm::vec3>& vertices = this->model.GetRawModel()->GetVertices();
    // initialization
    boundingBox.xMax = -std::numeric_limits<float>::infinity();
    boundingBox.yMax = -std::numeric_limits<float>::infinity();
    boundingBox.zMax = -std::numeric_limits<float>::infinity();
    boundingBox.xMin = std::numeric_limits<float>::infinity();
    boundingBox.yMin = std::numeric_limits<float>::infinity();
    boundingBox.zMin = std::numeric_limits<float>::infinity();

    for (glm::vec3 v: vertices)
    {
        // rotate the vertex
        glm::vec3 rotatedV;
        rotatedV = glm::rotate(v, rotation.z, glm::vec3(0, 0, 1));
        rotatedV = glm::rotate(v, rotation.y, glm::vec3(0, 1, 0));
        rotatedV = glm::rotate(v, rotation.x, glm::vec3(1, 0, 0));
        // compare
        if (rotatedV.x < boundingBox.xMin)
        {
            boundingBox.xMin = rotatedV.x;
        }

        if (rotatedV.x > boundingBox.xMax)
        {
            boundingBox.xMax = rotatedV.x;
        }

        if (rotatedV.y < boundingBox.yMin)
        {
            boundingBox.yMin = rotatedV.y;
        }

        if (rotatedV.y > boundingBox.yMax)
        {
            boundingBox.yMax = rotatedV.y;
        }

        if (rotatedV.z < boundingBox.zMin)
        {
            boundingBox.zMin = rotatedV.z;
        }

        if (rotatedV.z > boundingBox.zMax)
        {
            boundingBox.zMax = rotatedV.z;
        }
    }
    // don't forget to transform the AABB
    boundingBox.xMin += position.x;
    boundingBox.xMax += position.x;
    boundingBox.yMin += position.y;
    boundingBox.yMax += position.y;
    boundingBox.zMin += position.z;
    boundingBox.zMax += position.z;
#if DEBUG
    cerr << "bounding box: x(" << boundingBox.xMin <<", " << boundingBox.xMax << "), y(" << boundingBox.yMin << ", " << boundingBox.yMax << "), z(" << boundingBox.zMin << boundingBox.zMax << ")" << endl;
#endif
}
