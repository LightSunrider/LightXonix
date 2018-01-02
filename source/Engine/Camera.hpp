#pragma once

#include "Engine/GameObject.hpp"

#include <glm/gtc/quaternion.hpp>

using glm::mat4;
using glm::vec3;

namespace le {

class Camera : public GameObject {
public:
    explicit Camera() = default;

    explicit Camera(const Transform &transform, float fov, float aspect, float near, float far)
        : GameObject(transform), fov(fov), aspect(aspect), near(near), far(far) {}

    ~Camera() override = default;

    mat4 &ViewMatrix = m_ViewMatrix;
    mat4 &ProjectionMatrix = m_ProjectionMatrix;

    float fov = 45.0f;
    float aspect = 4.0f / 3.0f;
    float near = 0.1f;
    float far = 500.0f;

private:
    bool onUpdate(float delta) override {
        m_ViewMatrix = glm::mat4_cast(transform.rotation) * translate(mat4(), -transform.position);
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);

        return true;
    }

    mat4 m_ViewMatrix = mat4();
    mat4 m_ProjectionMatrix = mat4();
};
}
