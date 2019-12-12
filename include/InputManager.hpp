#pragma once

#include "Vec2.hpp"
#include <GLFW/glfw3.h>
#include <map>

//key to be watched and mouse

struct input
{
    std::map<int, bool> keys;
    Vec2f mouse_keys;
    Vec2d mouse;
};

class InputManager
{
private:
    GLFWwindow *m_window;
    input current_input;
    input old_input;

public:
    InputManager(GLFWwindow *);
    void update();
    bool keyUp(int key);
    bool keyDown(int key);
    bool isDown(int key);

    Vec2d getMousePosition();
    Vec2d getMouseOldPosition();
    Vec2d getMouseMovement();
};

inline InputManager::InputManager(GLFWwindow *window) : m_window{window}
{
    current_input.keys[GLFW_KEY_SPACE] = false;
    current_input.keys[GLFW_KEY_UP] = false;
    current_input.keys[GLFW_KEY_RIGHT] = false;
    current_input.keys[GLFW_KEY_LEFT] = false;
    current_input.keys[GLFW_KEY_DOWN] = false;
    current_input.keys[GLFW_KEY_W] = false;
    current_input.keys[GLFW_KEY_A] = false;
    current_input.keys[GLFW_KEY_S] = false;
    current_input.keys[GLFW_KEY_D] = false;
    current_input.keys[GLFW_KEY_LEFT_SHIFT] = false;
}

inline void InputManager::update()
{
    old_input = current_input;

    // Keyboard
    for (const auto &key : current_input.keys)
        current_input.keys[key.first] = (bool)glfwGetKey(m_window, key.first);

    //Mouse keys
    current_input.mouse_keys.x = (bool)glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
    current_input.mouse_keys.y = (bool)glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT);
    //Mouse
    glfwGetCursorPos(m_window, &current_input.mouse.x, &current_input.mouse.y);
}

inline bool InputManager::keyUp(int key)
{
    return old_input.keys[key] && !current_input.keys[key];
}

inline bool InputManager::keyDown(int key)
{
    return current_input.keys[key] && !old_input.keys[key];
}

inline bool InputManager::isDown(int key)
{
    return current_input.keys[key];
}

inline Vec2d InputManager::getMousePosition()
{
    return current_input.mouse;
}

inline Vec2d InputManager::getMouseOldPosition()
{
    return old_input.mouse;
}

inline Vec2d InputManager::getMouseMovement()
{
    return {current_input.mouse.x - old_input.mouse.x, current_input.mouse.y - old_input.mouse.y};
}