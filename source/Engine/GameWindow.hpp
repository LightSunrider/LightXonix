#pragma once

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

private:
    GLFWwindow *m_GlfwWindow = nullptr;

    int m_Width, m_Height;
    char *m_Title;

    void setSettings(GameWindowSettings settings);
};
