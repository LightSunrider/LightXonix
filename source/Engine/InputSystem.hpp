#pragma once
#include "Engine/KeyMap.hpp"
#include <glm/vec2.hpp>

struct GLFWwindow;

enum class MouseButton {
    Left = 0,
    Right = 1,
    Middle = 2,
    Four = 3,
    Five = 4,
    Six = 5,
    Seven = 6,
    Eight = 7
};

class InputSystem {
public:
    InputSystem(GLFWwindow* window);

    glm::vec2 GetCursorPosition();
    void SetCursorPosition(glm::vec2 cords);
    bool IsButtonPressed(int button);

    bool IsKeyPressed(Key key);

private:
    GLFWwindow *m_GlfwWindow = nullptr;

    double m_CursorX;
    double m_CursorY;
    bool m_MouseButtons[8];

    bool m_Keys[1024];

    void cursorPositionCallback(GLFWwindow* window, double posx, double posy);
    void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
