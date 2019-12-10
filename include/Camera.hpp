#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "Vec3.hpp"
#include "Entity.hpp"
#include "Mat4.hpp"

class Camera
{
private:
    float m_rotSpeed;
    float m_rotX;
    float m_rotY;
    float m_width;
    float m_height;
    Vec3  m_move;

public:
    Camera(float speed, unsigned int width, unsigned int height);
    


    Mat4 move_camera(GLFWwindow* window);
};

