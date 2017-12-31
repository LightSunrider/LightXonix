#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUv;
layout(location = 2) in vec3 vNormal;

out vec2 Uv;
out vec3 Position;
out vec3 ViewNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    Position = vec3(model * vec4(vPosition, 1.0));
    ViewNormal = normalize(mat3(transpose(inverse(model))) * vNormal);
    Uv = vUv;

    gl_Position = projection * view * vec4(Position, 1.0);
}
