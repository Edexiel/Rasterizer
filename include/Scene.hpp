#pragma once 

#include <vector>
#include "Entity.hpp"
#include "Camera.hpp"
#include "light.hpp"

class Scene
{
    Light _light;
    Camera _camera;
    InputManager* _im;
public:
    std::vector<Entity> entities;
    Scene(InputManager* im);
    ~Scene();

    Mat4 getView();
    Light getLight();

    void update(float deltaTime);
};

inline Mat4 Scene::getView()
{
    return _camera.getCameraMatrix();
}
inline Light Scene::getLight()
{
    return _light;
}

