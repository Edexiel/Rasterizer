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
    static void render_triangle(Vertex& v1, Vertex& v2, Vertex& v3, Texture *pTarget);
    static void render_point(Vertex& v1, Texture *pTarget);
    static float find_x_max_triangle(Vertex& v1, Vertex& v2, Vertex& v3);
    static float find_x_min_triangle(Vertex& v1, Vertex& v2, Vertex& v3);
    static float find_y_max_triangle(Vertex& v1, Vertex& v2, Vertex& v3);
    static float find_y_min_triangle(Vertex& v1, Vertex& v2, Vertex& v3);
};


