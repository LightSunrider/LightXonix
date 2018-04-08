#pragma once

#include "Engine/Shader.hpp"
#include "Engine/Texture.hpp"

namespace le {

class IMaterial {
public:
    virtual void Use() = 0;
};

class PhongMaterial : IMaterial {
public:
    PhongMaterial(Shader shader, Texture diffuse, Texture specular, float shininess)
        : shader(shader), diffuse(diffuse), specular(specular), shininess(shininess) {}

    void Use() override {
        shader.set("material.diffuse", 0, diffuse);
        shader.set("material.specular", 1, specular);
        shader.set("material.shininess", shininess);
    }

    Shader shader;
    Texture diffuse, specular;
    float shininess;
};
}
