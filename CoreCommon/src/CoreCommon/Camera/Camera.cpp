#include "Camera.hpp"

//SELF

//LIBS

//STD

using namespace core::common;

void Camera::setPosition(glm::vec3 newPos)
{
    position = newPos;
}

void Camera::setResolution(float x, float y)
{
    resolution = glm::vec2(x, y);
}

glm::mat4 Camera::getLookAt()
{
    // Construct look at matrix.
    // TODO - Allow view targets to be set for the camera.
    glm::vec3 forward = (position + glm::vec3(0, 0, 1));
    return glm::lookAt(position, forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getPerspective()
{
    return glm::perspectiveFov(fovR, resolution.x, resolution.y, nearZ, farZ);
}
