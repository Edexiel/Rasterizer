#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "Vec3.hpp"

// class Camera
// {
// public:
//     void move_camera(GLFWwindow* window, float& rotationX, float& rotationY, Vec3& pos, float& witdh, float& height);
// };

void move_camera(GLFWwindow* window, float& rotationX, float& rotationY, Vec3& pos, unsigned int& witdh, unsigned int& height);