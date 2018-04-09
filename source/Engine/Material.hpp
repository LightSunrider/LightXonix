#pragma once

#include "Engine/Shader.hpp"
#include "Engine/Texture.hpp"

namespace le {

class IMaterial {
public:
    virtual void Use(Shader &shader) = 0;
};

class PhongMaterial : IMaterial {
public:
    PhongMaterial(Texture diffuse, Texture specular, float shininess)
        : diffuse(diffuse), specular(specular), shininess(shininess) {}

    void Use(Shader &shader) override {
        shader.set("material.diffuse", 0, diffuse);
        shader.set("material.specular", 1, specular);
        shader.set("material.shininess", shininess);
    }

    Texture diffuse, specular;
    float shininess;
};
}
