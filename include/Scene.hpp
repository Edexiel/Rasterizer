#pragma once 

#include <vector>
#include "Entity.hpp"

class Scene
{
public:
    std::vector<Entity> entities;
    Scene();
    ~Scene();
};

