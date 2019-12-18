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

    // Initialize buffers
    clear_color_buffer();
    clear_depth_buffer();

    //Generate the texture to be sent to the GPU
    glGenTextures(1, &color_buffer_texture);

    //Upload an empty screen to the GPU (?)
    upload_texture();

    //Screen texture parameters
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //important
    glBindTexture(GL_TEXTURE_2D, 0);

    //set the view mode

    const float aspect = width / (float)height;

    viewport = Mat4::viewportMatrix(1, -1, width, height);
#if 1 // Perspective or 2D
    projection = Mat4::perspective(60.f, aspect, 0.01f, 10.f);
#elif
    projection = Mat4::orthoMatrix(-aspect, aspect, -1.f, 1.f, 0.f, 100.f);
#endif
}

void Rasterizer::render_scene(Scene *scene)
{
    //update camera matrix before transforming object
    view = scene->getView();

    for (Entity &entity : scene->entities)
    {
        switch (entity.getDrawMode())
        {
        // case POINT:
        // {
        //     // #pragma omp parallel for
        //     for (uint i = 0; i < entity.mesh->vertices.size(); i++)
        //         draw_point(entity.mesh->vertices[i], entity.transform);
        //     break;
        // }
        case TRIANGLE:
        {
            if (entity.mesh->indices.size() < 3)
                return;

            // #pragma omp parallel for
            for (uint i = 0; i < entity.mesh->indices.size() - 2; i += 3)
            {
                Vertex triangle[3]{entity.mesh->vertices[entity.mesh->indices[i]],
                                   entity.mesh->vertices[entity.mesh->indices[i + 1]],
                                   entity.mesh->vertices[entity.mesh->indices[i + 2]]};

                if (!entity.mesh->UV.empty())
                {
                    Vec2f uv[3]{entity.mesh->UV[i],
                                entity.mesh->UV[i + 1],
                                entity.mesh->UV[i + 2]};

                    draw_triangle(triangle, entity.transform, scene->getLight(), uv, entity.mesh->texture);
                }
                else
                {
                    draw_triangle(triangle, entity.transform, scene->getLight(), nullptr, entity.mesh->texture);
                }
            }

            break;
        }
        case LINE:
        {
            if (entity.mesh->indices.size() < 2)
                break;

            // #pragma omp parallel for
            for (uint i = 0; i < entity.mesh->indices.size() - 1; i += 1)
            {
                Vertex line[2]{entity.mesh->vertices[entity.mesh->indices[i]],
                               entity.mesh->vertices[entity.mesh->indices[i + 1]]};

                draw_line(line, entity.transform);
            }
            break;
        }
        default:
            break;
        }

        entity.resetTransformation();
    }
}

// void Rasterizer::draw_point(Vertex v, Mat4 &transformation)
// {
//     Mat4 mat_finale = viewport * projection * transformation;
//     v.position = (mat_finale * Vec4{v.position, 1}).xyz;
//     // viewport
//     set_pixel_color((uint)v.position.x, (uint)v.position.y, 0, v.color);
// }