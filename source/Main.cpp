#include "Engine/Engine.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace le;

signed main() {
    Window window = Window(800, 600, "LightXonix");

    Shader simpleShader = Shader("Shaders/simple.vert", "Shaders/simple.frag");
    Texture simpleTexture = Texture("Textures/simple.dds");
    Camera camera = Camera();
    Model cubeModel = Model("Models/cube.obj");

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    glm::vec2 lastPos;
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

    simpleShader.setInt("Texture", simpleTexture.Id);

    window.MakeContextCurrent();
    while (!window.ShouldClose()) {
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.PollEvents();
        ProcessInput();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        simpleShader.Use();
        camera.Update();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, simpleTexture.Id);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
        simpleShader.setMat4("projection", projection);
        simpleShader.setMat4("view", camera.ViewMatrix);

        for (uint i = 0; i < 10; i++) {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            simpleShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, cubeModel.Vertices.size());
        }

        /* skybox */ {
            glm::mat4 model;
            model = glm::translate(model, camera.Position);
            model = glm::scale(model, glm::vec3(500.0f, 500.0f, 500.0f));

            simpleShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, cubeModel.Vertices.size());
        }

        window.SwapBuffers();
        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
