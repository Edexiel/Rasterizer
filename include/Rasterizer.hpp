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
    static void draw_triangle(Vertex &v1, Vertex &v2, Vertex &v3, Texture &pTarget, uint width, uint height);
    static void draw_point(Vertex &v1, Texture &pTarget);

public:
    Rasterizer(uint *width, uint *height);
    ~Rasterizer();

    void render_scene(Scene *pScene);

    void draw_triangle(Vertex &v1, Vertex &v2, Vertex &v3, Mat4& transfo);
    void draw_point(Vertex &v1);
};
