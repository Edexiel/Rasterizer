#pragma once
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Entity.hpp"
#include "Mat4.hpp"
#include "InputManager.hpp"

class Camera
{
private:
    InputManager *_input;
    float _mouse_speed;
    float _movement_speed;
    // bool _capture;
    float _pitch;
    float _yaw;
    Vec3 _position;
    Vec3 _direction;

public:
    Camera() = default;
    Camera(InputManager *input, Vec3 position, float pitch, float yaw, float mouse_speed, float movement_speed);
    Vec3 getPosition();
    void update(float deltaTime);
    Mat4 getCameraMatrix();
};

inline Vec3 Camera::getPosition()
{
    return _position;
}
inline Mat4 Camera::getCameraMatrix()
{
    return Mat4::CreateXRotationMatrix(_pitch * (float)M_PI / 180.f) * Mat4::CreateYRotationMatrix(_yaw * (float)M_PI / 180.f) * Mat4::CreateTranslationMatrix(_position);
}