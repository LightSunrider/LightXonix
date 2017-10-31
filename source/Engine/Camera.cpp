#include "Engine/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

void NormalizeRotation(float &degrees) {
    degrees = (int(degrees) % 360) + (degrees - int(degrees));
}

void NormalizeRotation(glm::vec3 &vector) {
    NormalizeRotation(vector.x);
    NormalizeRotation(vector.y);
    NormalizeRotation(vector.z);
}

namespace le {

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : GameObject(position, rotation, scale) {}

void Camera::OnUpdate() {
    NormalizeRotation(Rotation);

    if (Rotation.x > 89.0f) {
        Rotation.x = 89.0f;
    }
    if (Rotation.x < -89.0f) {
        Rotation.x = -89.0f;
    }

    glm::quat pitch = glm::angleAxis(glm::radians(Rotation.x), glm::vec3(1, 0, 0));
    glm::quat yaw = glm::angleAxis(glm::radians(Rotation.y), glm::vec3(0, 1, 0));
    glm::quat roll = glm::angleAxis(glm::radians(Rotation.z), glm::vec3(0, 0, 1));

    m_Orientation = glm::normalize(pitch * yaw * roll);
    m_ViewMatrix = glm::mat4_cast(m_Orientation) * glm::translate(glm::mat4(), Position);
}

glm::vec3 Camera::getRight() const {
    return glm::conjugate(m_Orientation) * glm::vec3(-1.0, 0.0f, 0.0f);
}

glm::vec3 Camera::getForward() const {
    return glm::conjugate(m_Orientation) * glm::vec3(0.0f, 0.0f, -1.0f);
}
};
