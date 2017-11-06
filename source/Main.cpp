#include "Engine/Engine.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace le;

signed main() {
    Window window = Window(800, 600, "LightXonix");

    Shader phongShader = Shader("Shaders/PhongShader.vs", "Shaders/PhongShader.fs");
    Texture simpleTexture("Textures/simple.dds");
    Camera camera = Camera();
    Model cubeModel("Models/cube.obj");

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    glm::vec2 lastPos = window.Input.GetCursorPosition();
    auto ProcessInput = [&]() {
        if (window.Input.IsKeyPressed(Key::ESCAPE)) {
            window.Close();
            return;
        }

        if (window.Input.IsKeyPressed(Key::W)) {
            camera.Position += camera.getForward() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::S)) {
            camera.Position -= camera.getForward() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::A)) {
            camera.Position += camera.getRight() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::D)) {
            camera.Position -= camera.getRight() * deltaTime * 10.0f;
        }

        glm::vec2 cursorPos = window.Input.GetCursorPosition() - lastPos;
        lastPos = window.Input.GetCursorPosition();
        camera.Rotation.x += cursorPos.y * deltaTime * 10.0f;
        camera.Rotation.y += cursorPos.x * deltaTime * 10.0f;
    };

    // clang-format off
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  -2.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // clang-format on

    glEnable(GL_DEPTH_TEST);

    uint VBO;
    glGenVertexArrays(1, &VBO);
    glBindVertexArray(VBO);

    uint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(
        GL_ARRAY_BUFFER, cubeModel.Vertices.size() * sizeof(glm::vec3), &cubeModel.Vertices[0], GL_STATIC_DRAW);

    uint uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeModel.Uv.size() * sizeof(glm::vec2), &cubeModel.Uv[0], GL_STATIC_DRAW);

    uint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeModel.Normals.size() * sizeof(glm::vec3), &cubeModel.Normals[0], GL_STATIC_DRAW);

    uint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, cubeModel.Elements.size() * sizeof(ushort), &cubeModel.Elements[0], GL_STATIC_DRAW);

    window.MakeContextCurrent();
    while (!window.ShouldClose()) {
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.PollEvents();
        ProcessInput();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        phongShader.Use();
        camera.Update();

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
        phongShader.setMat4("Projection", projection);
        phongShader.setMat4("View", camera.ViewMatrix);

        phongShader.setVec3("Light.Position", glm::vec3(0.0f, 0.0f, 0.0f));
        phongShader.setVec3("Light.Color", glm::vec3(1.0f, 1.0f, 1.0f));
        phongShader.setFloat("Light.Power", 2.5f);

        phongShader.setVec3("Material.Ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        phongShader.setVec3("Material.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        phongShader.setVec3("Material.Specular", glm::vec3(0.3f, 0.3f, 0.3f));
        phongShader.setFloat("Material.Shininess", 64.f);

        phongShader.setTexture(0, "Texture", simpleTexture);

        for (uint i = 0; i < 10; i++) {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            phongShader.setMat4("Model", model);

            glDrawElements(GL_TRIANGLES, cubeModel.Elements.size(), GL_UNSIGNED_SHORT, nullptr);
        }

        /* skybox */ {
            glm::mat4 model;
            model = glm::translate(model, camera.Position);
            model = glm::scale(model, glm::vec3(500.0f, 500.0f, 500.0f));

            phongShader.setMat4("Model", model);

            glDrawElements(GL_TRIANGLES, cubeModel.Elements.size(), GL_UNSIGNED_SHORT, nullptr);
        }

        window.SwapBuffers();
        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
