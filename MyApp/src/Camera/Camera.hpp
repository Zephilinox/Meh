#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace meh::scene
{

class Camera
{
public:
    Camera() = default;

    void setPosition(glm::vec3 newPos);
    void setResolution(float x, float y);

    // Data Retrieval.
    glm::mat4 getLookAt();
    glm::mat4 getPerspective();

private:
    // Camera info
    glm::vec2 resolution;
    glm::vec3 position;
    glm::quat rotation;
    float fovR;
    float nearZ;
    float farZ;
};

}