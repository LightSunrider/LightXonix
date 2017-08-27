#include "Engine/InputSystem.hpp"
#include <GLFW/glfw3.h>

InputSystem::InputSystem(GLFWwindow* window){
    m_GlfwWindow = window;

    glfwSetCursorPosCallback(m_GlfwWindow, (*this).cursorPositionCallback);
    glfwSetMouseButtonCallback(m_GlfwWindow, (*this).mouseButtonCallback);
    glfwSetKeyCallback(m_GlfwWindow, (*this).keyCallback);

    for (size_t i = 0; i < 1024; i++){
        m_Keys[i] = false;
    }
    for (size_t i = 0; i < 8; i++) {
        m_MouseButtons[i] = false;
    }
}

glm::vec2 InputSystem::GetCursorPosition(){
    return glm::vec2(m_CursorX, m_CursorY);
}

void InputSystem::SetCursorPosition(glm::vec2 cords){
    glfwSetCursorPos(m_GlfwWindow, m_CursorX, m_CursorY);
}

bool InputSystem::IsButtonPressed(int button){
    return false;
}

bool InputSystem::IsKeyPressed(Key key){
    return false;
}

void InputSystem::cursorPositionCallback(GLFWwindow* window, double posx, double posy){
    m_CursorX = posx;
    m_CursorY = posy;
}

void InputSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button < 0 && button >= 8) {
        return;
    }

    if (action == GLFW_PRESS) {
        m_MouseButtons[button] = true;
    }
    else if (action == GLFW_RELEASE){
        m_MouseButtons[button] = false;
    }
}

void InputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key < 0 && key >= 1024) {
        return;
    }

    if (action == GLFW_PRESS) {
        m_Keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        m_Keys[key] = false;
    }
}
