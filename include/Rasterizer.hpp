#pragma once

#include "Texture.hpp"
#include "Scene.hpp"



class Rasterizer
{
private:
    uint *m_width;
    uint *m_height;

    Texture render_target;
    Texture depth_buffer;
    
    void draw_triangle(Vertex v1, Vertex v2, Vertex v3, Mat4& transfo);
    void draw_point(Vertex v1, Mat4& transfo);
    void draw_sphere();
    void get_viewport_pos(Vertex &v1);
public:
    Rasterizer(uint *width, uint *height);
    ~Rasterizer();

    void render_scene(Scene *pScene);
};
