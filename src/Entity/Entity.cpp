#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../config.hpp"
#include "Entity.hpp"

using namespace std;

Entity::Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isPickable, EntityType type): model(model), position(position), rotation(rotation), scale(scale), isPickable(isPickable), type(type)
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
    // @NOTE transform is not considered here, see GetAABB() for more information
#if DEBUG
    AABB box = GetAABB();
    cerr << "bounding box: x(" << box.xMin <<", " << box.xMax << "), y(" << box.yMin << ", " << box.yMax << "), z(" << box.zMin << ", " << box.zMax << ")" << endl;
#endif
}

AABB Entity::GetAABB() const
{
    AABB box;
    // don't forget to transform the AABB
    box.xMin = boundingBox.xMin + position.x;
    box.xMax = boundingBox.xMax + position.x;
    box.yMin = boundingBox.yMin + position.y;
    box.yMax = boundingBox.yMax + position.y;
    box.zMin = boundingBox.zMin + position.z;
    box.zMax = boundingBox.zMax + position.z;
    return box;
}
