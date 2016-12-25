#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera();
    ~Camera();
    void Update(GLfloat newYpos);
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
    void Move(GLfloat newYpos);
};

#endif
