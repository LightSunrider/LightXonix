#version 330 core
#pragma once

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
