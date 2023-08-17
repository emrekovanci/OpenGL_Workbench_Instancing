#include <Core/Camera.hpp>

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, LookPosition, Up);
}
