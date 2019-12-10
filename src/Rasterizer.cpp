#include <iostream>
#include <cstring>
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

Rasterizer::~Rasterizer() {}

void Rasterizer::render_scene(Scene *pScene)
{
    // TO DO : set the color in black
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
                draw_triangle(triangle, e.transfo, pScene->light);
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

void Rasterizer::draw_scene()
{
    glEnable(GL_TEXTURE_2D);
    upload_texture();
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    clear_color_buffer();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);

    glTexCoord2f(1, 1);
    glVertex2f(1, 1);

    glTexCoord2f(1, 0);
    glVertex2f(1, -1);

    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
}

void Rasterizer::clear_color_buffer()
{
    memset(color_buffer, 0xDF, m_width * m_height * sizeof(Color));
    // for (size_t i = 0; i < m_width * m_height; i++)
    //     color_buffer[i] = {255, 255, 255};

    // intrin_ZERO_float((float*)color_buffer,m_width * m_height);
}
void Rasterizer::clear_depth_buffer()
{
    // memset(color_buffer, 0xFF, m_width * m_height * sizeof(unsigned int));
    for (size_t i = 0; i < m_width * m_height; i++)
        depth_buffer[i] = 1.1f;
}

inline void Rasterizer::upload_texture() const
{
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * @brief Rasterization function of the program
 * 
 * @param vertices      screen-tranformed vertices
 * @param t_vetices     object matrix only tranformed vertices
 * @param t_normals     object matric only transformed normals
 * @param light         light source to use
 */
void Rasterizer::raster_triangle(Vertex (&vertices)[3], Vec4 (&t_vertices)[3], Vec4 (&t_normals)[3], Light &light)
{
    // shortcuts
    const Vertex &v1 = vertices[0];
    const Vertex &v2 = vertices[1];
    const Vertex &v3 = vertices[2];

    const int xMin = (int)max(min(min(v1.position.x, v2.position.x), v3.position.x), 0.f);
    const int yMin = (int)max(min(min(v1.position.y, v2.position.y), v3.position.y), 0.f);
    const int xMax = (int)min(max(max(v1.position.x, v2.position.x), v3.position.x), (float)m_width - 1);
    const int yMax = (int)min(max(max(v1.position.y, v2.position.y), v3.position.y), (float)m_height - 1);

    const Vec3 vec1{v2.position.x - v1.position.x, v2.position.y - v1.position.y, 0};
    const Vec3 vec2{v3.position.x - v1.position.x, v3.position.y - v1.position.y, 0};

    for (int y = yMin; y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {
            const Vec3 q{x - v1.position.x, y - v1.position.y, 0};

            const float w2 = Vec3::cross_product_z(q, vec2) / Vec3::cross_product_z(vec1, vec2);
            const float w3 = Vec3::cross_product_z(vec1, q) / Vec3::cross_product_z(vec1, vec2);
            const float w1 = 1.f - w2 - w3;

            if (w2 >= 0.f && w3 >= 0.f && w2 + w3 <= 1)
            {
                const float z = v1.position.z * w1 + v2.position.z * w2 + v3.position.z * w3;

                if (z <= depth_buffer[x + y * m_width])
                {

                    const Vec3 t_pos{t_vertices[0].xyz * w1 + t_vertices[1].xyz * w2 + t_vertices[2].xyz * w3};
                    const Vec3 t_normal{t_normals[0].xyz * w1 + t_normals[1].xyz * w2 + t_normals[2].xyz * w3};

                    Color t_color{v1.color * w1 + v2.color * w2 + v3.color * w3};

                    light.apply_light(t_pos, t_normal, t_color, light.camera_pos, light.light_pos);

                    // if (min(min(w1, w2), w3) < 0.016f)
                    // {
                    //     set_pixel_color(x, y, z, {(unsigned char)(255), (unsigned char)(255), (unsigned char)(255)});
                    // }
                    // else
                    // {
                    // std::cout << "x: " << x << "y: " << y << "z: " << z << std::endl;
                    set_pixel_color(x, y, z, t_color);
                }
                // }
            }
        }
    }
}

/**
 * @brief Entry point of the rasterization of a triangle 
 * 
 * @param vertices 
 * @param transformation 
 * @param light 
 */
void Rasterizer::draw_triangle(Vertex (&vertices)[3], Mat4 transformation, Light &light)
{
    // transform space: transformation * vec3      (4D)
    // clipSpace:            transformation * vec3 (4D) [-w,w]
    //      clipping out of bound triangles (0001 0010 0100)
    // NDC:  vec3/vec4.w                          (3D) [-1,1]
    //      Back face culling
    // Screen coordinate : viewport * ndc        (2D)

    Vec4 transCoord[3];
    Vec4 transNorm[3];
    for (short i = 0; i < 3; i++)
    {
        transCoord[i] = transformation * (Vec4){vertices[i].position, 1.f};
        transNorm[i] = transformation * (Vec4){vertices[i].normal, 0.f};
    }

    Vec4 clipCoord[3];
    for (short i = 0; i < 3; i++)
        clipCoord[i] = projection * transCoord[i];

    // clipping


    // Ne plus utiliser les clip coord a partir de ce point, elles ont ete homogeneisees
    Vec3 ndc[3];
    for (short i = 0; i < 3; i++)
        ndc[i] = clipCoord[i].homogenize().xyz;

    // back face culling
    if (Vec3::cross_product_z(ndc[1] - ndc[0], ndc[2] - ndc[0]) <= 0.f)
        return;

    Vertex screenCoord[3];
    for (short i = 0; i < 3; i++)
        screenCoord[i] = (Vertex){(viewport * (Vec4){ndc[i], 1.f}).xyz, vertices[i].color, vertices[i].normal};

    raster_triangle(screenCoord, transCoord, transNorm, light);
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

inline void Rasterizer::set_pixel_color(uint x, uint y, float z, const Color &c)
{
    // std::cout << z << std::endl;
    const uint index = x + y * m_width;

    color_buffer[index] = c;
    depth_buffer[index] = z;
}