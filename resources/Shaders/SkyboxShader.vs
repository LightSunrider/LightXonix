#version 330 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexUv;
layout(location = 2) in vec3 VertexNormal;

out vec2 Uv;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0f);

    Uv = VertexUv;
}
