#pragma once

#include <glm/glm.hpp>

namespace le {

class GameObject {
public:
    GameObject(glm::vec3 position = glm::vec3(), glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3()) {
        this->Position = position;
        this->Rotation = rotation;
        this->Scale = scale;
    }

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale; 

private:
    void OnCreate() { };
    void OnUpdate() { };
    void OnDestroy() { };
};
}
