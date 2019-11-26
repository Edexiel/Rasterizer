#pragma once

#include "Texture.hpp"
#include "Scene.hpp"

enum
{
    POINT,
    TRIANGLE,
    TRIANGLE_STRIP,
    FORM
};

class Rasterizer
{
private:
    uint *m_width;
    uint *m_height;

    Texture render_target;
    
    void draw_triangle(Vertex v1, Vertex v2, Vertex v3, Mat4& transfo);
    void draw_point(Vertex v1, Mat4& transfo);
    void draw_sphere();
    void get_viewport_pos(Vec3 &v1);
public:
    Rasterizer(uint *width, uint *height);
    ~Rasterizer();

    void render_scene(Scene *pScene);
};
