#pragma once

struct GLFWwindow;

struct GameWindowSettings {
    int Width = 800, Height = 600;
    char *Title = (char *)"";
};

class GameWindow {
public:
    GameWindow();
    GameWindow(int m_Width, int m_Height, char *m_Title);
    GameWindow(GameWindowSettings settings);

    void Close();

    bool &ShouldClose = m_ShouldClose;

private:
    GLFWwindow *m_GlfwWindow;

    int m_Width, m_Height;
    char *m_Title;
    bool m_ShouldClose;

    void setSettings(GameWindowSettings settings);
};
