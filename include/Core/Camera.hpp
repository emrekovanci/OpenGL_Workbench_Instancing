#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::vec3 Position { 0.0f, 0.0f, 3.0f };
    glm::vec3 Up { 0.0f, 1.0f, 0.0f };
    glm::vec3 LookPosition { 0.0f, 0.0f, 0.0f };

    glm::mat4 getViewMatrix() const;
};