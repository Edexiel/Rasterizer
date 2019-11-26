#pragma once

#include "Texture.hpp"
#include "Scene.hpp"

#define Z_FAR 9999;
#define Z_NEAR 0;

class Rasterizer
{
private:
    uint m_width;
    uint m_height;

    Color*  color_buffer;
    float*  depth_buffer;

     GLuint color_buffer_texture;
     GLuint depth_buffer_texture;
    
    void draw_triangle(Vertex v1, Vertex v2, Vertex v3, Mat4& transfo);
    void draw_point(Vertex v1, Mat4& transfo);
    void draw_sphere();
    void get_viewport_pos(Vec3 &v1);
public:
    Rasterizer(uint width, uint height);
    ~Rasterizer();

    void draw_scene();
    void render_scene(Scene *pScene);
    void clear_color_buffer();
    void clear_depth_buffer();
    void upload_texture() const;
    void set_pixel_color(uint x,uint y,uint z,const Color &c);
};
