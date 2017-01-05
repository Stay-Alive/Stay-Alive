#include <GL/glew.h>
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

void Camera::Update(GLfloat newYpos, const vector<Entity>& entities)
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

    Move(newYpos, entities);
    return;
}

void Camera::Move(GLfloat newYpos, const vector<Entity>& entities)
{
    GLfloat speedUp = 1;
    GLFWwindow *window = glfwGetCurrentContext();
    glm::vec3 newPosition = position;
    newPosition.y = newYpos + YOUR_HEIGHT;
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
        newPosition += verticalStep;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))  // down
    {
        newPosition -= verticalStep;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))  // left, @NOTE which is vertical to our viewDirection
    {
        newPosition -= horizontalStep;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))  // right
    {
        newPosition += horizontalStep;
    }

    if (-1 == DetectCollision(newPosition, entities))  // no collision
    {
        position = newPosition;
    }

    else
    {
        // @TODO what to do when collision is detected
    }

    return;
}

int Camera::DetectCollision(glm::vec3 newPosition, const vector<Entity>& entities)
{
    int ret = -1;
    int i = 0;
    for (const Entity& entity: entities)
    {
        AABB box = entity.GetAABB();
        if (box.xMin < newPosition.x && box.xMax > newPosition.x
            && box.yMin < newPosition.y && box.yMax > newPosition.y - YOUR_HEIGHT
            && box.zMin < newPosition.z && box.zMax > newPosition.z)
        {
            ret = i;  // found the first entity that we ran into
            break;
        }
        i++;
    }
    return ret;
}
