#include <iostream>
#include "Camera.hpp"
#include "cmath"

Camera::Camera(float speed, unsigned int width, unsigned int height) : m_rotSpeed{speed}, m_rotX{0}, m_rotY{0}, m_width{width}, m_height{height}, m_move{Vec3{0.f, 0.f, 2.0f}} {}

Mat4 Camera::move_camera(GLFWwindow *window)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    x -= (m_width / 2);
    y -= (m_height / 2);

    m_rotX += y * m_rotSpeed;
    m_rotY += x * m_rotSpeed;

    float advanceSpeed = 0.f;
    if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W))
        advanceSpeed = -0.05f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S))
        advanceSpeed = 0.05f;

    m_move.x += advanceSpeed * -sinf(m_rotY);
    m_move.z += advanceSpeed * cosf(m_rotY);

    float strafeSpeed = 0.f;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
        strafeSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
        strafeSpeed = -0.05f;
    if (glfwGetKey(window, GLFW_KEY_SPACE))
        m_move.y += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        m_move.y -= 0.05f;

    m_move.x += strafeSpeed * cosf(m_rotY);
    m_move.z += strafeSpeed * sinf(m_rotY);

    //create matrix camera

    glfwSetCursorPos(window, m_width / 2, m_height / 2);

    return    Mat4::CreateXRotationMatrix(m_rotX)  * Mat4::CreateYRotationMatrix(m_rotY) * Mat4::CreateTranslationMatrix(m_move);
}