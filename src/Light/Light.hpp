#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
//#include "ClockTime.hpp"

class SimpleLight
{
public:
    SimpleLight(glm::vec3 position, glm::vec3 color): position(position), color(color) {}
    ~SimpleLight() {}

    inline void SetColor(const glm::vec3& color)
    {
        this->color = color;
    }

    inline void SetPosition(const glm::vec3& position)
    {
        this->position = position;
    }

    inline glm::vec3 GetPosition() const
    {
        return position;
    }

    inline glm::vec3 GetColor() const
    {
        return color;
    }

    void UpdateLight(int ThisTime);

private:
    glm::vec3 position;
    glm::vec3 color;
};
#endif
