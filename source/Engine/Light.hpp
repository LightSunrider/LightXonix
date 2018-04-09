#pragma once

#include "Engine/Shader.hpp"

#include <glm/vec3.hpp>
#include <iostream>
#include <string>

using glm::vec3;

namespace le {

class ILight {
public:
    virtual void Use(int arrayIndex, Shader& shader) = 0;
};

class PointLight : ILight {
public:
    PointLight() = default;

    explicit PointLight(vec3 position) : Position(position) {}

    void Use(int arrayIndex, Shader& shader) override {
        std::string a = "pointLights[" + std::to_string(arrayIndex) + "]";

        _set(shader, a, ".position", Position);
        _set(shader, a, ".ambient", Ambient);
        _set(shader, a, ".diffuse", Diffuse);
        _set(shader, a, ".specular", Specular);
        _set(shader, a, ".constant", Constant);
        _set(shader, a, ".linear", Linear);
        _set(shader, a, ".quadratic", Quadratic);
    }

    vec3 Position = vec3(0.0f);

    vec3 Ambient = vec3(0.35f);
    vec3 Diffuse = vec3(0.95f);
    vec3 Specular = vec3(1.0f);

    float Constant = 1.0f;
    float Linear = 0.09f;
    float Quadratic = 0.032f;

private:
    template <typename T> inline void _set(Shader& shader, std::string& arr, const char* var, T& val) {
        shader.set((arr + var).c_str(), val);
    }
};
}
