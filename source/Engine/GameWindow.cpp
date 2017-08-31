#include "Engine/GameWindow.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

bool GameWindow::s_LibrariesInitalized = false;

GameWindow::GameWindow() {
    GameWindowSettings settings;

    createWindow(settings);
}

GameWindow::GameWindow(int Width, int Height, char *Title) {
    GameWindowSettings settings;

    settings.Width = Width;
    settings.Height = Height;
    settings.Title = Title;

    createWindow(settings);
}

GameWindow::GameWindow(GameWindowSettings settings) {
    createWindow(settings);
}

void GameWindow::PollEvents() {
    glfwPollEvents();
}

void GameWindow::Close() {
    glfwSetWindowShouldClose(m_GlfwWindow, true);
}

void GameWindow::MakeContextCurrent() {
    glfwMakeContextCurrent(m_GlfwWindow);
}

void GameWindow::SwapBuffers() {
    glfwSwapBuffers(m_GlfwWindow);
}

bool GameWindow::ShouldClose() {
    return (bool) glfwWindowShouldClose(m_GlfwWindow);
}

void GameWindow::createWindow(GameWindowSettings settings) {
    // GLFW initialization
    if (s_LibrariesInitalized == false) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

    m_GlfwWindow = glfwCreateWindow(settings.Width, settings.Height, settings.Title, NULL, NULL);
    MakeContextCurrent();

    // GLEW initialization
    if (s_LibrariesInitalized == false) {
        glewExperimental = GL_TRUE;
        glewInit();

        s_LibrariesInitalized = true;
    }

    m_Input = InputSystem(m_GlfwWindow);
    glfwSetInputMode(m_GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    updateSettings(settings);
}

void GameWindow::updateSettings(GameWindowSettings settings) {
    if (m_Settings.Width != settings.Width || m_Settings.Height != settings.Height) {
        glfwSetWindowSize(m_GlfwWindow, settings.Width, settings.Height);
    }

    if (m_Settings.Title != settings.Title) {
        glfwSetWindowTitle(m_GlfwWindow, settings.Title);
    }

    m_Settings = settings;
}
