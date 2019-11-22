#pragma once 

#include "Texture.hpp"
#include "Scene.hpp"


enum
{
    POINT,
    TRIANGLE,

    FORM
};

class Rasterizer
{
public:
    Rasterizer();
    ~Rasterizer();
    void render_scene(Scene* pScene, Texture* pTarget);
    void render_triangle(Vertex& v1, Vertex& v2, Vertex& v3, Texture *pTarget);
    void render_point(Vertex& v1, Texture *pTarget);
};


