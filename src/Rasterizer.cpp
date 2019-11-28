#include <iostream>
#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
#include "cmath"
#include "Mat4.hpp"
#include "math.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "cstring"

Rasterizer::Rasterizer(uint width, uint height) : m_width{width}, m_height{height}, ambientLight{0.50}
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
                break;

            for (uint i = 0; i < e.mesh->indices.size() - 2; i += 3)
                draw_triangle(e.mesh->vertices[e.mesh->indices[i]], e.mesh->vertices[e.mesh->indices[i + 1]], e.mesh->vertices[e.mesh->indices[i + 2]], e.transfo);
            break;
        }
        case LINE:
        {
            if (e.mesh->indices.size() < 2)
                break;

            for (uint i = 0; i < e.mesh->indices.size() - 1; i += 1)
                draw_line(e.mesh->vertices[e.mesh->indices[i]], e.mesh->vertices[e.mesh->indices[i + 1]], e.transfo);
            draw_line(e.mesh->vertices[e.mesh->indices[e.mesh->indices.size() - 1]], e.mesh->vertices[e.mesh->indices[0]], e.transfo);
            break;
        }

        default:
            break;
        }
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
    memset(color_buffer, 0xFF, m_width * m_height * sizeof(Color));
    // for (size_t i = 0; i < width *height; i++)
    //     pixels[i] = {0xFF,0x00,0x00};
}
void Rasterizer::clear_depth_buffer()
{
    // memset(color_buffer, 0xFF, m_width * m_height * sizeof(unsigned int));
    for (size_t i = 0; i < m_width * m_height; i++)
        depth_buffer[i] = -1;
}

void Rasterizer::upload_texture() const
{
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Rasterizer::draw_triangle(Vertex v1, Vertex v2, Vertex v3, Mat4 &transformation)
{
    // Mat4 ortho {{2/(aspect+aspect), 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {-((aspect-aspect)/(aspect+aspect)),-(0 /2),-(1 +- 1), 1}};
    Mat4 mat_finale = projection * viewport * transformation;

    v1.position = (mat_finale * Vec4{v1.position, 1}).xyz;
    v2.position = (mat_finale * Vec4{v2.position, 1}).xyz;
    v3.position = (mat_finale * Vec4{v3.position, 1}).xyz;

    Vec3 vec1{v2.position.x - v1.position.x, v2.position.y - v1.position.y, 0};
    Vec3 vec2{v3.position.x - v1.position.x, v3.position.y - v1.position.y, 0};

    uint xMin = min(min(v1.position.x, v2.position.x), v3.position.x) - 1;
    uint xMax = max(max(v1.position.x, v2.position.x), v3.position.x) + 1;
    uint yMin = min(min(v1.position.y, v2.position.y), v3.position.y) - 1;
    uint yMax = max(max(v1.position.y, v2.position.y), v3.position.y) + 1;

    // TO DO : change the width and the height
    if (xMin < 0)
        xMin = 0;
    if (xMax > m_width)
        xMax = m_width;
    if (yMin < 0)
        yMin = 0;
    if (yMax > m_height)
        yMax = m_height;

    for (uint y = yMin; y < yMax; y++)
    {
        for (uint x = xMin; x < xMax; x++)
        {
            Vec3 q{x - v1.position.x, y - v1.position.y, 0};
            //AVX
            float w1 = cross_product(q, vec2) / cross_product(vec1, vec2);
            float w2 = cross_product(vec1, q) / cross_product(vec1, vec2);
            float w3 = 1.f - w1 - w2;
            // float minW = min(min(w1, w2), w3);

            if (w1 >= 0.f && w2 >= 0.f && w1 + w2 <= 1)
            {
            //     if (minW < 0.01f)
            //     {
            //         float z = v1.position.z * w1 + v2.position.z * w2 + v3.position.z * w3;
            //         set_pixel_color(x, y, z, {255 * ambientLight, 255 * ambientLight, 255 * ambientLight});
            //     }
            //     else
                {
                    float z = v1.position.z * w1 + v2.position.z * w2 + v3.position.z * w3;
                    set_pixel_color(x, y, z, {v1.color * w3 * ambientLight + v2.color * w1 * ambientLight + v3.color * w2 * ambientLight});
                }
            }
        }
    }
}

void Rasterizer::draw_line(Vertex v1, Vertex v2, Mat4 &transformation)
{
    Mat4 mat_finale = viewport * projection * transformation;
    v1.position = (mat_finale * Vec4{v1.position, 1}).xyz;
    v2.position = (mat_finale * Vec4{v2.position, 1}).xyz;

    const bool steep = (fabs(v2.position.y - v1.position.y) > fabs(v2.position.x - v1.position.x));
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
    const float dy = fabs(v2.position.y - v1.position.y);

    float error = dx / 2.0f;
    const int ystep = (v1.position.y < v2.position.y) ? 1 : -1;
    int y = (int)v1.position.y;

    const int maxX = (int)v2.position.x;

    for (int x = (int)v1.position.x; x < maxX; x++)
    {
        if (steep)
        {
            set_pixel_color(y, x, 0, v1.color * ambientLight);
        }
        else
        {
            set_pixel_color(x, y, 0, v1.color * ambientLight);
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
    set_pixel_color(v.position.x, v.position.y, 0, v.color * ambientLight);
}

void Rasterizer::set_pixel_color(uint x, uint y, uint z, const Color &c)
{
    if (z < depth_buffer[x + y * m_width])
    {
    }
    color_buffer[x + y * m_width] = c;
    depth_buffer[x + y * m_width] = z;
}