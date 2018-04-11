#version 330 core

in vec2 Uv;

out vec3 Color;

uniform sampler2D skybox;

void main() {
    Color = texture(skybox, Uv).rgb;
}
