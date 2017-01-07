#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include "../Model/TexturedModel.hpp"

enum EntityType {Food, Wood, Stone, Monster, Others};
/*
interface for AABB:

AABB Entity::GetAABB();  // get bounding box

void Entity::ComputeAABB(glm::vec3 position, glm::vec3 rotation);  // compute the bounding box, which is done in constructor, @NOTE if one entity is rotated or transformed, AABB needs to recompute

*/

typedef struct
{
    GLfloat xMin;
    GLfloat xMax;
    GLfloat yMin;
    GLfloat yMax;
    GLfloat zMin;
    GLfloat zMax;
}AABB;

class Entity
{
public:
    // @NOTE rotation.{x, y, z} means the rotation degree around corresponding axis
    Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isPickable = false, EntityType type = Others);

    void ComputeAABB(glm::vec3 position, glm::vec3 rotation);

    inline TexturedModel GetModel() const
    {
        return model;
    }

    inline glm::vec3 GetPosition() const
    {
        return position;
    }

    inline glm::vec3 GetRotation() const
    {
        return rotation;
    }

    inline glm::vec3 GetScale() const
    {
        return scale;
    }

    inline void SetPosition(glm::vec3 position)
    {
        this->position = position;
    }

    inline void SetRotation(glm::vec3 rotation)
    {
        this->rotation = rotation;
    }

    inline void SetScale(glm::vec3 scale)
    {
        this->scale = scale;
    }

    inline void ModifyPosition(glm::vec3 deltaPosition)
    {
        this->position += deltaPosition;
    }

    inline void ModifyRotation(glm::vec3 deltaRotation)
    {
        this->rotation += deltaRotation;
    }

    inline void ModifyScale(glm::vec3 deltaScale)
    {
        this->scale += deltaScale;
    }

    AABB GetAABB() const;

    inline bool GetIsPickable() const
    {
        return isPickable;
    }

    inline EntityType GetType() const
    {
        return type;
    }

private:
    TexturedModel model;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    AABB boundingBox;
    bool isPickable;
    EntityType type;
};

#endif
