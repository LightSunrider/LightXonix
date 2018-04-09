#include "Engine/Engine.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace le;
using namespace glm;

signed main() {
    Window window(800, 600, "LightXonix");
    Camera camera;

    Shader::PreprocSettings preprocSettings;
    preprocSettings.Definitions.insert(std::make_pair("POINT_LIGHTS", "1"));
    preprocSettings.IncludePath = "Shaders/";

    Shader phongShader = Shader("Shaders/PhongShader.vs", "Shaders/PhongShader.fs", preprocSettings);
    Shader skyboxShader = Shader("Shaders/SkyboxShader.vs", "Shaders/SkyboxShader.fs", preprocSettings);

    Texture simpleTexture("Textures/simple.dds");
    Texture skyboxTexture("Textures/skybox.dds");
    Texture emptyTexture;

    PhongMaterial phongMaterial(simpleTexture, emptyTexture, 64.0f);

    Mesh cubeModel("Models/cube.obj");
    Mesh skyboxModel("Models/skybox.obj");

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    vec2 lastPos = window.Input.GetCursorPosition();
    auto ProcessInput = [&]() {
        if (window.Input.IsKeyPressed(Key::ESCAPE)) {
            window.Close();
            return;
        }

        if (window.Input.IsKeyPressed(Key::W)) {
            camera.transform.position += camera.transform.Forward() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::S)) {
            camera.transform.position -= camera.transform.Forward() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::A)) {
            camera.transform.position += camera.transform.Right() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::D)) {
            camera.transform.position -= camera.transform.Right() * deltaTime * 10.0f;
        }

        vec2 cursorPos = window.Input.GetCursorPosition() - lastPos;
        lastPos = window.Input.GetCursorPosition();

        float pitch = cursorPos.y * deltaTime * 10.0f;
        float yaw = cursorPos.x * deltaTime * 10.0f;

        quat quatPitch = angleAxis(radians(pitch), vec3(1, 0, 0));
        quat quatYaw = angleAxis(radians(yaw), vec3(0, 1, 0));

        camera.transform.rotation = normalize(quatPitch * camera.transform.rotation * quatYaw);
    };

    // clang-format off
    vec3 cubePositions[] = {
        vec3( 0.0f,  0.0f, -2.0f),
        vec3( 2.0f,  5.0f, -15.0f),
        vec3(-1.5f, -2.2f, -2.5f),
        vec3(-3.8f, -2.0f, -12.3f),
        vec3( 2.4f, -0.4f, -3.5f),
        vec3(-1.7f,  3.0f, -7.5f),
        vec3( 1.3f, -2.0f, -2.5f),
        vec3( 1.5f,  2.0f, -2.5f),
        vec3( 1.5f,  0.2f, -1.5f),
        vec3(-1.3f,  1.0f, -1.5f)
    };
    // clang-format on

    glEnable(GL_DEPTH_TEST);

    // Cube
    uint cubeVBO;
    glGenVertexArrays(1, &cubeVBO);
    glBindVertexArray(cubeVBO);

    uint cubeVertexBuffer;
    glGenBuffers(1, &cubeVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeModel.Vertices.size() * sizeof(vec3), &cubeModel.Vertices[0], GL_STATIC_DRAW);

    uint cubeUvBuffer;
    glGenBuffers(1, &cubeUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubeUvBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeModel.Uv.size() * sizeof(vec2), &cubeModel.Uv[0], GL_STATIC_DRAW);

    uint cubeNormalBuffer;
    glGenBuffers(1, &cubeNormalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cubeNormalBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeModel.Normals.size() * sizeof(vec3), &cubeModel.Normals[0], GL_STATIC_DRAW);

    uint cubeElementBuffer;
    glGenBuffers(1, &cubeElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeElementBuffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, cubeModel.Elements.size() * sizeof(ushort), &cubeModel.Elements[0], GL_STATIC_DRAW);

    // Skybox
    uint skyboxVBO;
    glGenVertexArrays(1, &skyboxVBO);
    glBindVertexArray(skyboxVBO);

    uint skyboxVertexBuffer;
    glGenBuffers(1, &skyboxVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeModel.Vertices.size() * sizeof(vec3), &skyboxModel.Vertices[0], GL_STATIC_DRAW);

    uint skyboxUvBuffer;
    glGenBuffers(1, &skyboxUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxUvBuffer);
    glBufferData(GL_ARRAY_BUFFER, skyboxModel.Uv.size() * sizeof(vec2), &skyboxModel.Uv[0], GL_STATIC_DRAW);

    uint skyboxNormalBuffer;
    glGenBuffers(1, &skyboxNormalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxNormalBuffer);
    glBufferData(GL_ARRAY_BUFFER, skyboxModel.Normals.size() * sizeof(vec3), &skyboxModel.Normals[0], GL_STATIC_DRAW);

    uint skyboxElementBuffer;
    glGenBuffers(1, &skyboxElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, skyboxModel.Elements.size() * sizeof(ushort), &skyboxModel.Elements[0],
                 GL_STATIC_DRAW);

    window.MakeContextCurrent();
    while (!window.ShouldClose()) {
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.PollEvents();
        ProcessInput();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(deltaTime);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, cubeUvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, cubeNormalBuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeElementBuffer);

        phongShader.Use();

        phongShader.set("projection", camera.ProjectionMatrix);
        phongShader.set("view", camera.ViewMatrix);
        phongShader.set("cameraPosition", camera.transform.position);

        phongShader.set("pointLights[0].position", vec3(0.0f, 0.0f, 0.0f));
        phongShader.set("pointLights[0].ambient", vec3(0.35f, 0.35f, 0.35f));
        phongShader.set("pointLights[0].diffuse", vec3(0.95f, 0.95f, 0.95f));
        phongShader.set("pointLights[0].specular", vec3(1.0f, 1.0f, 1.0f));
        phongShader.set("pointLights[0].constant", 1.0f);
        phongShader.set("pointLights[0].linear", 0.09f);
        phongShader.set("pointLights[0].quadratic", 0.032f);

        phongMaterial.Use(phongShader);

        for (uint i = 0; i < 10; i++) {
            mat4 model;
            model = translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));

            phongShader.set("model", model);

            glDrawElements(GL_TRIANGLES, cubeModel.Elements.size(), GL_UNSIGNED_SHORT, nullptr);
        }

        /* skybox */ {
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, skyboxVertexBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, skyboxUvBuffer);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, skyboxNormalBuffer);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxElementBuffer);

            skyboxShader.Use();

            mat4 model;
            model = translate(model, camera.transform.position);
            model = scale(model, vec3(500.0f, 500.0f, 500.0f));

            skyboxShader.set("Model", model);
            skyboxShader.set("Projection", camera.ProjectionMatrix);
            skyboxShader.set("View", camera.ViewMatrix);
            skyboxShader.set("Texture", 0, skyboxTexture);

            glDrawElements(GL_TRIANGLES, skyboxModel.Elements.size(), GL_UNSIGNED_SHORT, nullptr);
        }

        window.SwapBuffers();
        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
