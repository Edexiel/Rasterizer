#include "Camera.hpp"
#include "cmath"


void move_camera(GLFWwindow* window, float& rotationX, float& rotationY, Vec3& pos, unsigned int& witdh, unsigned int& height)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    x -= (witdh / 2);
    y -= (height / 2);

    rotationX += y *  -0.005f;
    rotationY += x *  0.005f;

    float angle = rotationY * M_PI;

    float advanceSpeed = 0.f;
    if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W))
        advanceSpeed = 0.05;
    if (glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S))
        advanceSpeed = -0.05;

    pos.x+= advanceSpeed * -sin(angle);
    pos.z += advanceSpeed *  cos(angle);


    float strafeSpeed = 0.f;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
        strafeSpeed = -0.05;  
    if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
        strafeSpeed = 0.05;
    if (glfwGetKey(window, GLFW_KEY_SPACE))
        pos.y += 0.05;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        pos.y -= 0.05;

    pos.x += strafeSpeed * cos(angle);
    pos.z += strafeSpeed * sin(angle);

    glfwSetCursorPos(window,  witdh / 2,  height / 2);
}