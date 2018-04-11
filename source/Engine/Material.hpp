#pragma once

#include "Engine/Shader.hpp"
#include "Engine/Texture.hpp"

namespace le {

class IMaterial {
public:
    virtual void Use(Shader &shader) = 0;

    virtual ~IMaterial() = default;
};

class PhongMaterial : public IMaterial {
public:
    PhongMaterial(Texture diffuse, Texture specular, float shininess)
        : diffuse(diffuse), specular(specular), shininess(shininess) {}

    virtual ~PhongMaterial() = default;

    void Use(Shader &shader) override {
        shader.set("material.diffuse", 0, diffuse);
        shader.set("material.specular", 1, specular);
        shader.set("material.shininess", shininess);
    }

    Texture diffuse, specular;
    float shininess;
};

class SkyboxMaterial : public IMaterial {
public:
    SkyboxMaterial(Texture skybox) : skybox(skybox) {}

    virtual ~SkyboxMaterial() = default;

    void Use(Shader &shader) override {
        shader.set("skybox", 0, skybox);
    }

    Texture skybox;
};
}
