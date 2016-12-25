#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "../config.hpp"
#include "Camera.hpp"

using namespace std;

Camera::Camera()
{
    GLFWwindow *window = glfwGetCurrentContext();
    position = glm::vec3(0, YOUR_HEIGHT, 0);  // suppose that you are 1.8m tall
    viewDirection = glm::vec3(0, 0, -1);  // view at -z axis @NOTE it should be normalized
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + viewDirection, this->UP);
}

void Camera::Update(GLfloat newYpos)
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
    glm::vec3 rotateYAxisNormal(glm::cross(viewDirection, UP));  // compute the cross product(your right hand side)
    glm::mat4 rotateXvec(glm::rotate(-deltaMousePos.x * SENSITIVITY, UP));
    glm::mat4 rotateYvec(glm::rotate(-deltaMousePos.y * SENSITIVITY, rotateYAxisNormal));
    glm::mat3 rotateXAndY(glm::mat3(rotateYvec * rotateXvec)); // construct a 3-by-3 matrix

	viewDirection = glm::normalize(rotateXAndY * viewDirection);

    this->mousePos = newMousePos;

    Move(newYpos);
    return;
}

void Camera::Move(GLfloat newYpos)
{
    GLfloat speedUp = 1;
    GLFWwindow *window = glfwGetCurrentContext();
    position.y = newYpos + YOUR_HEIGHT;
    // hold shift to speed up
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
    {
        speedUp *= 5;  // 3 times faster
    }

    glm::vec3 verticalStep(viewDirection.x, 0, viewDirection.z);
    verticalStep = SPEED * speedUp * verticalStep;
    glm::vec3 horizontalStep(glm::cross(verticalStep, UP));

    // transform
    if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W))  // up
    {
        // @NOTE we are always in x-z plane
        position += verticalStep;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))  // down
    {
        position -= verticalStep;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))  // left, @NOTE which is vertical to our viewDirection
    {
        position -= horizontalStep;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))  // right
    {
        position += horizontalStep;
    }

    if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
    {
#if DEBUG
        cerr << "Captured an escape\n";
#endif
        glfwTerminate();
        exit(0);
    }
    return;
}
