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
    Camera(InputManager *input, Vec3 position, float pitch, float yaw, float mouse_speed, float movement_speed);
    
    void update(float deltaTime);
    Mat4 getCameraMatrix();
};
