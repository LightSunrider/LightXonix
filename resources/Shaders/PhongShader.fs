#version 330 core

#getdefine POINT_LIGHTS

#include "Light/PointLight.glsl"
#include "Material/PhongMaterial.glsl"

in vec2 Uv;
in vec3 Position;
in vec3 ViewNormal;

out vec4 Color;

uniform vec3 cameraPosition;
uniform PointLight pointLights[POINT_LIGHTS];
uniform Material material;

void main() {
    vec3 viewDirection = normalize(cameraPosition - Position);

    vec3 result;
    for (int i = 0; i < POINT_LIGHTS; i++) {
        result += CalculatePointLight(pointLights[i], material, Uv, ViewNormal, Position, viewDirection);
    }

    Color = vec4(result, 1.0);
}
