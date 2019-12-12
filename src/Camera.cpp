#include <iostream>
#include "Camera.hpp"
#include "InputManager.hpp"
#include "cmath"

Camera::Camera(InputManager *input, float speed) : _input{input},
                                                   _rotSpeed{speed},
                                                   _rotation{Vec2d{0., 0.}},
                                                   _move{Vec3{0.f, 0.f, 0.0f}} {}

Mat4 Camera::getCameraMatrix()
{
    Vec2d mouse = _input->getMouseMovement();

    _rotation.x += (float)mouse.y * _rotSpeed;
    _rotation.y += (float)mouse.x * _rotSpeed;

    float advanceSpeed = 0.f;
    if (_input->isDown(GLFW_KEY_UP) || _input->isDown(GLFW_KEY_W))
        advanceSpeed = -0.05f;
    if (_input->isDown(GLFW_KEY_DOWN) || _input->isDown(GLFW_KEY_S))
        advanceSpeed = 0.05f;

    _move.x += advanceSpeed * -sinf((float)_rotation.x);
    _move.z += advanceSpeed * cosf((float)_rotation.y);

    float strafeSpeed = 0.f;

    if (_input->isDown(GLFW_KEY_RIGHT) || _input->isDown(GLFW_KEY_D))
        strafeSpeed = 0.05f;
    if (_input->isDown(GLFW_KEY_LEFT) || _input->isDown(GLFW_KEY_A))
        strafeSpeed = -0.05f;
    if (_input->isDown(GLFW_KEY_SPACE))
        _move.y += 0.05f;
    if (_input->isDown(GLFW_KEY_LEFT_SHIFT))
        _move.y -= 0.05f;

    _move.x += strafeSpeed * cosf((float)_rotation.x);
    _move.z += strafeSpeed * sinf((float)_rotation.y);

    return Mat4::CreateXRotationMatrix((float)_rotation.x) * Mat4::CreateYRotationMatrix((float)_rotation.y) * Mat4::CreateTranslationMatrix(_move);
}