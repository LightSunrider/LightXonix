#version 330 core

struct sLight {
    vec3 Position;
    vec3 Color;
    float Power;
    float Distance;
};

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexUv;
layout(location = 2) in vec3 VertexNormal;

out vec2 Uv;
out vec3 Position;
out vec3 ViewNormal;
out vec3 ViewDirection;
out vec3 LightDirection;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform sLight Light;

void main() {
    gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0f);

    Position = (Model * vec4(VertexPosition, 1)).xyz;
    ViewDirection = vec3(0, 0, 0) - (View * Model * vec4(VertexPosition, 1)).xyz;
    LightDirection = (View * vec4(Light.Position, 1)).xyz + ViewDirection;
    ViewNormal = mat3(transpose(inverse(Model))) * VertexNormal;
    Uv = VertexUv;
}
