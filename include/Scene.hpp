#pragma once 

#include <vector>
#include "Entity.hpp"
#include "light.hpp"

class Scene
{
public:
    std::vector<Entity> entities;
    light m_light;
    Scene();
    ~Scene();
};

