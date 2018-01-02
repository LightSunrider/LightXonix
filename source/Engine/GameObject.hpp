#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

using glm::mat4;
using glm::quat;
using glm::vec3;

void NormalizeRotation(float &degrees) {
    degrees = (int(degrees) % 360) + (degrees - int(degrees));
}

namespace le {

class Transform {
public:
    explicit Transform(vec3 position = vec3(), quat rotation = quat(), vec3 scale = vec3(1.0f))
        : position(position), rotation(rotation), scale(scale) {}

    virtual ~Transform() = default;

    mat4 Matrix() {
        mat4 m;

        m = glm::translate(m, position);
        m *= glm::mat4_cast(rotation);
        m = glm::scale(m, scale);

        return m;
    }

    vec3 Up() {
        return glm::conjugate(rotation) * vec3(0.0, 1.0f, 0.0f);
    }

    vec3 Right() {
        return glm::conjugate(rotation) * vec3(-1.0, 0.0f, 0.0f);
    }

    vec3 Forward() {
        return glm::conjugate(rotation) * vec3(0.0, 0.0f, -1.0f);
    }

    void Rotate(vec3 eulerAngles) {
        eulerAngles = glm::radians(eulerAngles);

        eulerAngles.x += glm::pitch(rotation);
        eulerAngles.y += glm::yaw(rotation);
        eulerAngles.z += glm::roll(rotation);

        glm::quat pitch = glm::angleAxis(eulerAngles.x, glm::vec3(1, 0, 0));
        glm::quat yaw = glm::angleAxis(eulerAngles.y, glm::vec3(0, 1, 0));
        glm::quat roll = glm::angleAxis(eulerAngles.z, glm::vec3(0, 0, 1));

        quat a(eulerAngles);

        rotation = glm::normalize(roll * yaw * pitch);
    }

    vec3 position;
    quat rotation;
    vec3 scale;
};

class GameObject {
public:
    GameObject() = default;

    explicit GameObject(const Transform &transform) : transform(transform) {}

    virtual ~GameObject() = default;

    bool Update(float delta) {
        return onUpdate(delta);
    }

    Transform transform;

private:
    virtual bool onUpdate(float delta) {
        return true;
    }
};
}
