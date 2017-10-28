#pragma once

#include "Engine/GameObject.hpp"

#include <glm/gtc/quaternion.hpp>

namespace le {
class Camera : public GameObject {
public:
    Camera(glm::vec3 position = glm::vec3(), glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3());

    glm::mat4 &ViewMatrix = m_ViewMatrix;
    glm::quat &Orientation = m_Orientation;

    glm::vec3 getRight() const;
    glm::vec3 getForward() const;

    void Update() {
        OnUpdate();
    }

private:
    void OnUpdate();

    glm::quat m_Orientation = glm::quat();
    glm::mat4 m_ViewMatrix = glm::mat4();
};
}
