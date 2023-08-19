#include <Core/Camera.hpp>

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, LookPosition, Up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const
{
    return glm::perspective(glm::radians(FieldOfView), aspect, 0.1f, 100.0f);
}
