#include <iostream>
#include <cmath>

#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"
#include "tools.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "light.hpp"
#include "Texture.hpp"

Rasterizer::Rasterizer(uint width, uint height) : m_width{width}, m_height{height}
{
    color_buffer = new Color[width * height];
    depth_buffer = new float[width * height];

    clear_color_buffer();
    clear_depth_buffer();

    glGenTextures(1, &color_buffer_texture);

    upload_texture();

    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Rasterizer::render_scene(Scene *pScene)
{
    for (Entity &e : pScene->entities)
    {
        switch (e.getDrawMode())
        {
        case POINT:
        {
            for (uint i = 0; i < e.mesh->vertices.size(); i++)
                draw_point(e.mesh->vertices[i], e.transfo);
            break;
        }
        case TRIANGLE:
        {
            if (e.mesh->indices.size() < 3)
                return;

            for (uint i = 0; i < e.mesh->indices.size() - 2; i += 3)
            {
                Vertex triangle[3]{e.mesh->vertices[e.mesh->indices[i]], e.mesh->vertices[e.mesh->indices[i + 1]], e.mesh->vertices[e.mesh->indices[i + 2]]};
                Vec2 UVarray[3]{e.mesh->UV[i], e.mesh->UV[i + 1], e.mesh->UV[i + 2]};
                draw_triangle(triangle, e.transfo, pScene->light, UVarray);
            }

            break;
        }
        case LINE:
        {
            if (e.mesh->indices.size() < 2)
                break;

            for (uint i = 0; i < e.mesh->indices.size() - 1; i += 1)
            {
                draw_line(e.mesh->vertices[e.mesh->indices[i]], e.mesh->vertices[e.mesh->indices[i + 1]], e.transfo);
            }
            // draw_line(e.mesh->vertices[e.mesh->indices[e.mesh->indices.size() - 1]], e.mesh->vertices[e.mesh->indices[0]], e.transfo);
            break;
        }
        default:
            break;
        }

        e.resetTransformation();
    }
}

void Rasterizer::draw_line(Vertex v1, Vertex v2, Mat4 &transformation)
{
    Mat4 mat_finale = viewport * projection * transformation;

    v1.position = (mat_finale * Vec4{v1.position, 1}).xyz;
    v2.position = (mat_finale * Vec4{v2.position, 1}).xyz;

    const bool steep = (fabsf(v2.position.y - v1.position.y) > fabsf(v2.position.x - v1.position.x));
    if (steep)
    {
        std::swap(v1.position.x, v1.position.y);
        std::swap(v2.position.x, v2.position.y);
    }

    if (v1.position.x > v2.position.x)
    {
        std::swap(v1.position.x, v2.position.x);
        std::swap(v1.position.y, v2.position.y);
    }

    const float dx = v2.position.x - v1.position.x;
    const float dy = fabsf(v2.position.y - v1.position.y);

    float error = dx / 2.0f;
    const int ystep = (v1.position.y < v2.position.y) ? 1 : -1;
    int y = (int)v1.position.y;

    const int maxX = (int)v2.position.x;

    for (int x = (int)v1.position.x; x < maxX; x++)
    {
        if (steep)
        {
            set_pixel_color(y, x, 0, v1.color);
        }
        else
        {
            set_pixel_color(x, y, 0, v1.color);
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void Rasterizer::draw_point(Vertex v, Mat4 &transformation)
{
    Mat4 mat_finale = viewport * projection * transformation;
    v.position = (mat_finale * Vec4{v.position, 1}).xyz;
    // viewport
    set_pixel_color((uint)v.position.x, (uint)v.position.y, 0, v.color);
}