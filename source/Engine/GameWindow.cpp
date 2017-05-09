#include "Engine/GameWindow.hpp"
#include <GLFW/glfw3.h>

GameWindow::GameWindow(int Width, int Height, char *Title) {
    GameWindowSettings settings;

    settings.Width = Width;
    settings.Height = Height;
    settings.Title = Title;

    setSettings(settings);
}

GameWindow::GameWindow() {
    GameWindowSettings settings;

    setSettings(settings);
}

GameWindow::GameWindow(GameWindowSettings settings) {
    setSettings(settings);
}

void GameWindow::setSettings(GameWindowSettings settings) {
    glfwInit();
    if (m_GlfwWindow == nullptr) {
        m_GlfwWindow = glfwCreateWindow(800, 600, "", NULL, NULL);
    }

    m_Width = settings.Width;
    m_Height = settings.Height;
    m_Title = settings.Title;

    glfwSetWindowSize(m_GlfwWindow, m_Width, m_Height);
    glfwSetWindowTitle(m_GlfwWindow, m_Title);
}

void GameWindow::Close() {
    m_ShouldClose = true;

    glfwWindowShouldClose(m_GlfwWindow);
}
