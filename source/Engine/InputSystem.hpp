#pragma once
#include "Engine/KeyMap.hpp"
#include <glm/vec2.hpp>
#include <unordered_map>

struct GLFWwindow;

enum class MouseButton { Left = 0, Right = 1, Middle = 2, Four = 3, Five = 4, Six = 5, Seven = 6, Eight = 7 };

class InputSystem {
public:
    InputSystem();
    InputSystem(GLFWwindow* window);

    ~InputSystem();

    glm::vec2 GetCursorPosition();
    void SetCursorPosition(glm::vec2 cords);
    bool IsButtonPressed(int button);

    bool IsKeyPressed(Key key);

private:
    struct InputSystemData {
        float m_CursorX;
        float m_CursorY;
        bool m_MouseButtons[8];

        char m_Keys[1024];
    };

    typedef std::unordered_map<GLFWwindow*, InputSystem::InputSystemData*> InputSystemMap;

    static InputSystemMap s_InputSystemMap;

    GLFWwindow* m_GlfwWindow = nullptr;

    InputSystemData* m_Data;

    static void cursorPositionCallback(GLFWwindow* window, double posx, double posy);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
