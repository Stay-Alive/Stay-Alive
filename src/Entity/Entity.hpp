#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include "../Model/TexturedModel.hpp"

class Entity
{
public:
    Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): model(model), position(position), rotation(rotation) {}

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

    inline void SetModel(const TexturedModel& model)
    {
        this->model = model;
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

private:
    TexturedModel model;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif
