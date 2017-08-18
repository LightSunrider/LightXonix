#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 InvertedUV;

out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(Position, 1.0f);
    UV = vec2(InvertedUV.x, 1.0 - InvertedUV.y);
}
