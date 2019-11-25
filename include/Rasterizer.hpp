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
private:
    uint *m_width;
    uint *m_height;

    Texture render_target;
    
    void draw_triangle(Vertex &v1, Vertex &v2, Vertex &v3);
    void draw_point(Vertex &v1);
public:
    Rasterizer(uint *width, uint *height);
    ~Rasterizer();

    void render_scene(Scene *pScene);

};
