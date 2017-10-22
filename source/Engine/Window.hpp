#pragma once

#include "Engine/InputSystem.hpp"

struct GLFWwindow;

namespace le {
struct WindowSettings {
    int Width = 800, Height = 600;
    std::string Title = "";

    WindowSettings() = default;
};

class Window {
public:
    Window();
    Window(int m_Width, int m_Height, const char *m_Title);
    Window(WindowSettings &settings);

    void PollEvents();
    void Close();
    void MakeContextCurrent();
    void SwapBuffers();
    bool ShouldClose();

    InputSystem &Input = m_Input;

private:
    static bool s_LibrariesInitialized;

    GLFWwindow *m_GlfwWindow = nullptr;
    InputSystem m_Input;

    WindowSettings m_Settings;

    void createWindow(WindowSettings settings);
    void updateSettings(WindowSettings settings);
};
