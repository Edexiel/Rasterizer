#include <iostream>
#include "Camera.hpp"
#include "InputManager.hpp"
#include "cmath"

Camera::Camera(InputManager *input, Vec3 position, float pitch, float yaw, float mouse_speed, float movement_speed) : _input{input},
                                                                                                                      _mouse_speed{mouse_speed},
                                                                                                                      _movement_speed{movement_speed},
                                                                                                                      _pitch{pitch},
                                                                                                                      _yaw{yaw},
                                                                                                                      _position{position}
{
}

void Camera::update(float deltaTime)
{
    Vec2d mouse = _input->getMouseMovement();

    _pitch += (float)mouse.y * _mouse_speed;
    if (_pitch > 90.f)
        _pitch = 90.f;
    if (_pitch < -90.f)
        _pitch = -90.f;

    _yaw += (float)mouse.x * _mouse_speed;
    if (_yaw > 180.f)
        _yaw = -180.f;
    if (_yaw < -180.f)
        _yaw = 180.f;

    _direction.x = sinf(_yaw * (float)M_PI / 180.f) * _movement_speed * deltaTime;
    _direction.z = -cosf(_yaw * (float)M_PI / 180.f) * _movement_speed * deltaTime;
    _direction.y = 0;

    if (_input->isDown(GLFW_KEY_UP) || _input->isDown(GLFW_KEY_W))
    {
        _position = _position - _direction;
    }
    else if (_input->isDown(GLFW_KEY_DOWN) || _input->isDown(GLFW_KEY_S))
    {
        _position = _position + _direction;
    }

    if (_input->isDown(GLFW_KEY_RIGHT) || _input->isDown(GLFW_KEY_D))
    {
        _position.x += _direction.z;
        _position.z -= _direction.x;
    }
    else if (_input->isDown(GLFW_KEY_LEFT) || _input->isDown(GLFW_KEY_A))
    {
        _position.x -= _direction.z;
        _position.z += _direction.x;
    }

    if (_input->isDown(GLFW_KEY_SPACE))
    {
        _position.y -= _movement_speed * deltaTime;
    }
    else if (_input->isDown(GLFW_KEY_LEFT_SHIFT))
    {
        _position.y += _movement_speed * deltaTime;
    }
}