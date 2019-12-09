#pragma once

#include "Texture.hpp"
#include "Scene.hpp"
#include "light.hpp"
#include "Vertex.hpp"

class Rasterizer
{
private:
    uint m_width;
    uint m_height;

    Color *color_buffer;
    float *depth_buffer;

    GLuint color_buffer_texture;

    void draw_triangle(Vertex (&vertices)[3], Mat4 transformation, Light &light);
    void raster_triangle(Vertex (&vertices)[3], Light &light);

    void draw_line(Vertex v1, Vertex v2, Mat4 &transfo);
    void draw_point(Vertex v1, Mat4 &transfo);
    void draw_sphere();
    inline void set_pixel_color(uint x, uint y, float z, const Color &c);
    void upload_texture() const;

public:
    Rasterizer(uint width, uint height);
    ~Rasterizer();

    Mat4 projection;
    Mat4 viewport;

    void draw_scene();
    void render_scene(Scene *pScene);
    void clear_color_buffer();
    void clear_depth_buffer();
};
