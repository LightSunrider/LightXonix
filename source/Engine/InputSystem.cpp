#include "Engine/InputSystem.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

namespace le {

InputSystem::InputSystemMap InputSystem::s_InputSystemMap = InputSystem::InputSystemMap();

InputSystem::InputSystem() {
    m_GlfwWindow = nullptr;
    m_Data = nullptr;
}

InputSystem::InputSystem(GLFWwindow* window) {
    m_GlfwWindow = window;
    m_Data = new InputSystemData();
    s_InputSystemMap.insert(std::pair<GLFWwindow*, InputSystemData*>(window, m_Data));

    glfwSetCursorPosCallback(m_GlfwWindow, cursorPositionCallback);
    glfwSetMouseButtonCallback(m_GlfwWindow, mouseButtonCallback);
    glfwSetKeyCallback(m_GlfwWindow, keyCallback);

    for (size_t i = 0; i < 1024; i++) {
        m_Data->m_Keys[i] = false;
    }
    for (size_t i = 0; i < 8; i++) {
        m_Data->m_MouseButtons[i] = false;
    }
    m_Data->m_CursorX = 0.0f;
    m_Data->m_CursorY = 0.0f;
}

glm::vec2 InputSystem::GetCursorPosition() {
    return glm::vec2(m_Data->m_CursorX, m_Data->m_CursorY);
}

void InputSystem::SetCursorPosition(glm::vec2 cords) {
    m_Data->m_CursorX = cords.x;
    m_Data->m_CursorY = cords.y;

    glfwSetCursorPos(m_GlfwWindow, m_Data->m_CursorX, m_Data->m_CursorY);
}

bool InputSystem::IsButtonPressed(MouseButton button) {
    return m_Data->m_MouseButtons[(int) button];
}

bool InputSystem::IsKeyPressed(Key key) {
    return m_Data->m_Keys[(int) key];
}

void InputSystem::cursorPositionCallback(GLFWwindow* window, double posx, double posy) {
    InputSystemData* input = s_InputSystemMap[window];

    input->m_CursorX = (float) posx;
    input->m_CursorY = (float) posy;
}

void InputSystem::Destroy() {
    auto input = s_InputSystemMap.find(m_GlfwWindow);
    if (input != s_InputSystemMap.end()) {
        s_InputSystemMap.erase(s_InputSystemMap.find(m_GlfwWindow));
    }

    if (m_Data != nullptr) {
        delete m_Data;
        m_Data = nullptr;
    }
}

void InputSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button < 0 && button >= 8) {
        return;
    }

    InputSystemData* input = s_InputSystemMap[window];

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        input->m_MouseButtons[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        input->m_MouseButtons[button] = false;
    }
}

void InputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key < 0 && key >= 1024) {
        return;
    }

    InputSystemData* input = s_InputSystemMap[window];

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        input->m_Keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        input->m_Keys[key] = false;
    }
}
}
