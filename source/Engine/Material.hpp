#pragma once

#include "Engine/Shader.hpp"
#include "Engine/Texture.hpp"

namespace le {

class IMaterial {
public:
    virtual void Use() = 0;
    virtual Shader* GetShader() = 0;

    virtual ~IMaterial() = default;
};

class PhongMaterial : public IMaterial {
public:
    PhongMaterial(Shader shader, Texture diffuse, Texture specular, float shininess)
        : shader(shader), diffuse(diffuse), specular(specular), shininess(shininess) {}

    virtual ~PhongMaterial() = default;

    void Use() override {
        shader.Use();
        shader.set("material.diffuse", 0, diffuse);
        shader.set("material.specular", 1, specular);
        shader.set("material.shininess", shininess);
    }

    Shader* GetShader() final {
        return &shader;
    }

    Shader shader;

    Texture diffuse, specular;
    float shininess;
};

class SkyboxMaterial : public IMaterial {
public:
    SkyboxMaterial(Shader shader, Texture skybox) : shader(shader), skybox(skybox) {}

    ~SkyboxMaterial() final = default;

    void Use() final {
        shader.Use();
        shader.set("skybox", 0, skybox);
    }

    Shader* GetShader() final {
        return &shader;
    }

    Shader shader;

    Texture skybox;
};
}
