#include "Engine/Window.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace le {

bool Window::s_LibrariesInitalized = false;

Window::Window() {
    WindowSettings settings;

    createWindow(settings);
}

Window::Window(int Width, int Height, char *Title) {
    WindowSettings settings;

    settings.Width = Width;
    settings.Height = Height;
    settings.Title = Title;

    createWindow(settings);
}

Window::Window(WindowSettings settings) {
    createWindow(settings);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::Close() {
    glfwSetWindowShouldClose(m_GlfwWindow, true);
    m_Input.Destroy();
}

void Window::MakeContextCurrent() {
    glfwMakeContextCurrent(m_GlfwWindow);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_GlfwWindow);
}

bool Window::ShouldClose() {
    return (bool) glfwWindowShouldClose(m_GlfwWindow);
}

void Window::createWindow(WindowSettings settings) {
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
        gl3wInit();

        s_LibrariesInitalized = true;
    }

    m_Input = InputSystem(m_GlfwWindow);
    glfwSetInputMode(m_GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    updateSettings(settings);
}

void Window::updateSettings(WindowSettings settings) {
    if (m_Settings.Width != settings.Width || m_Settings.Height != settings.Height) {
        glfwSetWindowSize(m_GlfwWindow, settings.Width, settings.Height);
    }

    if (m_Settings.Title != settings.Title) {
        glfwSetWindowTitle(m_GlfwWindow, settings.Title);
    }

    m_Settings = settings;
}
}
