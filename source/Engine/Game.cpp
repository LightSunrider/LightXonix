#include "Engine/Game.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>

void Game::Run() {
    glfwInit();
    glewInit();

    Initialize();
    LoadContent();

    long lastFrame = clock(),
        currentFrame;
    float delta = 0.0f;

    while (!Window.ShouldClose()) {
        currentFrame = clock();
        delta = (float) (currentFrame-lastFrame) / 1000;
        Update(delta);
        Window.MakeContextCurrent();
        Draw(delta);
        Window.SwapBuffers();
        Window.PollEvents();
        lastFrame = currentFrame;
    }
    Window.Close();
    UnloadContent();
    Dispose();
}
