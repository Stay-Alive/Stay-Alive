#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Entity/Entity.hpp"

using namespace std;

class Camera
{
public:
    Camera();
    ~Camera();
    int Update(GLfloat newYpos, const vector<Entity>& entities);  // return nonnegative number if collision detected
    glm::mat4 GetViewMatrix() const;


    inline glm::vec3 GetPosition() const
    {
        return position;
    }

    inline glm::vec3 GetViewDirection() const
    {
        return viewDirection;
    }
private:
    glm::vec3 position;
    glm::vec3 viewDirection;
    glm::vec2 mousePos;
    const glm::vec3 UP = glm::vec3(0, 1, 0);
    const GLfloat SENSITIVITY = 0.005f;
    const GLfloat SPEED = 0.1f;
    int Move(GLfloat newYpos, const vector<Entity>& entities);
    int DetectCollision(glm::vec3 newPosition, const vector<Entity>& entities);
};

#endif
