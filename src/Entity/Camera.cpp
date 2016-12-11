#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Camera.hpp"

using namespace std;

Camera::Camera()
{
    position = glm::vec3(0, 1.8, 0);
    viewDirection = glm::vec3(0, 1.8, -1);
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + viewDirection, this->UP);
}

void Camera::Update()
{
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    glm::vec2 newMousePos(x, y);
    glm::vec2 deltaMousePos(newMousePos - this->mousePos);

    if (glm::length(deltaMousePos) > 100)  // too far, we just do nothing
    {
        this->mousePos = newMousePos;
        return;
    }
    
    // rotate
}
