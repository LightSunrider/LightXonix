#version 330 core

struct sLight {
    vec3 Position;
    vec3 Color;
    float Power;
};

struct sMaterial {
    vec3 Ambient;
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

in vec2 Uv;
in vec3 Position;
in vec3 ViewNormal;
in vec3 ViewDirection;
in vec3 LightDirection;

out vec3 Color;

uniform sLight Light;
uniform sMaterial Material;

void main() {
    vec3 materialDiffuse = texture(Material.Diffuse, Uv).rgb;
    vec3 materialAmbient = Material.Ambient * materialDiffuse;
    vec3 materialSpecular = texture(Material.Specular, Uv).rgb;

    vec3 normal = normalize(ViewNormal);
    vec3 lightDirection = normalize(LightDirection);

    float distance = length(Light.Position - Position);
    float cosTheta = clamp(dot(normal, lightDirection), 0, 1);
    float cosAlpha = clamp(dot(normal, reflect(-lightDirection, normal)), 0, 1);

    materialDiffuse *= Light.Color * Light.Power * cosTheta / pow(distance, 2);
    materialSpecular *= Light.Color * Light.Power * pow(cosAlpha, Material.Shininess) / pow(distance, 2);

    Color = materialAmbient + materialDiffuse + materialSpecular;
}
