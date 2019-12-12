#pragma once

#include "Vec3.hpp"
#include "Entity.hpp"
#include "Mat4.hpp"
#include "InputManager.hpp"

class Camera
{
private:
    InputManager* _input;
    float _rotSpeed;
    Vec2d _rotation;
    Vec3  _move;

public:
    Camera(InputManager*,float speed);

    Mat4 getCameraMatrix();
};

