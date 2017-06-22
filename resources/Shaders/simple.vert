#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 InvertedUV;

out vec2 UV;

void main() {
    gl_Position = vec4(Position, 1.0f);
    UV = vec2(InvertedUV.x, 1.0 - InvertedUV.y);
}
