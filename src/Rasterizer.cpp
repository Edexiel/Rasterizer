#include "Rasterizer.hpp"

#include <iostream>
#include <cmath>

#include "Mat4.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "tools.hpp"

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
// #pragma omp parallel for
            for (uint i = 0; i < e.mesh->vertices.size(); i++)
                draw_point(e.mesh->vertices[i], e.transform);
            break;
        }
        case TRIANGLE:
        {
            if (e.mesh->indices.size() < 3)
                return;

// #pragma omp parallel for
            for (uint i = 0; i < e.mesh->indices.size() - 2; i += 3)
            {
                Vertex triangle[3]{e.mesh->vertices[e.mesh->indices[i]], e.mesh->vertices[e.mesh->indices[i + 1]], e.mesh->vertices[e.mesh->indices[i + 2]]};
                if (!e.mesh->UV.empty())
                {
                    Vec2f UVarray[3]{e.mesh->UV[i], e.mesh->UV[i + 1], e.mesh->UV[i + 2]};
                    draw_triangle(triangle, e.transform, pScene->light, UVarray, e.mesh->texture);
                }
                else
                {
                    draw_triangle(triangle, e.transform, pScene->light, nullptr, e.mesh->texture);
                }
            }

            break;
        }
        case LINE:
        {
            if (e.mesh->indices.size() < 2)
                break;
#pragma omp parallel for
            for (uint i = 0; i < e.mesh->indices.size() - 1; i += 1)
            {
                Vertex line[2]{e.mesh->vertices[e.mesh->indices[i]], e.mesh->vertices[e.mesh->indices[i + 1]]};
                draw_line(line, e.transform);
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



void Rasterizer::draw_point(Vertex v, Mat4 &transformation)
{
    Mat4 mat_finale = viewport * projection * transformation;
    v.position = (mat_finale * Vec4{v.position, 1}).xyz;
    // viewport
    set_pixel_color((uint)v.position.x, (uint)v.position.y, 0, v.color);
}