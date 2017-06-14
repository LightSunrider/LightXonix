#include "Engine/GameWindow.hpp"
#include "Engine/Shader.hpp"
#include <ctime>
#include <iostream>

signed main() {
    GameWindow window = GameWindow(800, 600, "LightXonix");

    Shader simpleShader = Shader("Shaders/simple.vert", "Shaders/simple.frag");

    GLfloat vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};
    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    long lastFrame = clock(), currentFrame;
    float delta = 0.0f;

    window.MakeContextCurrent();
    while (!window.ShouldClose()) {
        currentFrame = clock();
        delta = (float) (currentFrame - lastFrame) / 1000;

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        simpleShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.SwapBuffers();
        window.PollEvents();

        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
