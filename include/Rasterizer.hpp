#pragma once 

#include "Texture.hpp"
#include "Scene.hpp"

class Rasterizer
{
private:

public:
    Rasterizer();
    ~Rasterizer();
    void render_scene(Scene* pScene, Texture* pTarget);
};


