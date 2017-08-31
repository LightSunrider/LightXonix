#pragma once
#include "Engine/InputSystem.hpp"
#include <functional>

struct GLFWwindow;

struct GameWindowSettings {
    int Width = 800, Height = 600;
    char *Title = (char *) "";

    GameWindowSettings() {}
};

class GameWindow {
public:
    GameWindow();
    GameWindow(int m_Width, int m_Height, char *m_Title);
    GameWindow(GameWindowSettings settings);

    void PollEvents();
    void Close();
    void MakeContextCurrent();
    void SwapBuffers();
    bool ShouldClose();

    InputSystem &Input = m_Input;

private:
    static bool s_LibrariesInitalized;

    GLFWwindow *m_GlfwWindow = nullptr;
    InputSystem m_Input;

    GameWindowSettings m_Settings;

    void createWindow(GameWindowSettings settings);
    void updateSettings(GameWindowSettings settings);
};
