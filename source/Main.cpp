#include "Engine/Engine.hpp"
#include <ctime>
#include <iostream>

signed main() {
    GameWindow window = GameWindow(800, 600, "LightXonix");

    Shader simpleShader = Shader("Shaders/simple.vert", "Shaders/simple.frag");
    Texture simpleTexture = Texture("Textures/simple.dds");

    // clang-format off
    GLfloat vertices[] = {
        // Position          // UV
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 
        -0.5f, 0.5f, 0.0f,   0.0f, 1.0f};
    GLuint indices[] = {
        0, 1, 3, 
        1, 2, 3
    };
    // clang-format on

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, simpleTexture.Id);
        glUniform1i(glGetUniformLocation(simpleShader.Id, "Texture"), 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window.SwapBuffers();
        window.PollEvents();

        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
