#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
