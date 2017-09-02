#include "Engine/Engine.hpp"
#include <GLFW/glfw3.h>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
GLfloat lastX = 400, lastY = 300;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


signed main() {
    GameWindow window = GameWindow(800, 600, "LightXonix");

    Shader simpleShader = Shader("Shaders/simple.vert", "Shaders/simple.frag");
    Texture simpleTexture = Texture("Textures/simple.dds");

    auto ProcessInput = [&]() {
        if (window.Input.IsKeyPressed(Key::ESCAPE)) {
            window.Close();
            return;
        }

        if (window.Input.IsKeyPressed(Key::W)) {
            camera.ProcessKeyboard(FORWARD, deltaTime);
        }
        if (window.Input.IsKeyPressed(Key::S)) {
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        }
        if (window.Input.IsKeyPressed(Key::A)) {
            camera.ProcessKeyboard(LEFT, deltaTime);
        }
        if (window.Input.IsKeyPressed(Key::D)) {
            camera.ProcessKeyboard(RIGHT, deltaTime);
        }

        glm::vec2 cursorPos = window.Input.GetCursorPosition();

        if (firstMouse) {
            lastX = cursorPos.x;
            lastY = cursorPos.y;
            firstMouse = false;
        }

        GLfloat xoffset = cursorPos.x - lastX;
        GLfloat yoffset = lastY - cursorPos.y;// Reversed since y-coordinates go from bottom to left

        lastX = cursorPos.x;
        lastY = cursorPos.y;

        camera.ProcessMouseMovement(xoffset, yoffset);
    };

    // clang-format off
    GLfloat vertices[] = {
        // Position          // UV
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // clang-format on

    glEnable(GL_DEPTH_TEST);

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    window.MakeContextCurrent();
    while (!window.ShouldClose()) {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        simpleShader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, simpleTexture.Id);
        glUniform1i(glGetUniformLocation(simpleShader.Id, "Texture"), 0);

        // Create camera transformation
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection;
        projection = glm::perspective(camera.Zoom, (float) 800 / (float) 600, 0.1f, 1000.0f);

        GLint modelLoc = glGetUniformLocation(simpleShader.Id, "model");
        GLint viewLoc = glGetUniformLocation(simpleShader.Id, "view");
        GLint projLoc = glGetUniformLocation(simpleShader.Id, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);

        glm::mat4 model;
        model = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (GLfloat) glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        window.SwapBuffers();
        window.PollEvents();

        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
