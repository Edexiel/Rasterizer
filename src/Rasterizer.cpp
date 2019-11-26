#include <iostream>
#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
// #include "cmath"
#include "Mat4.hpp"
#include "math.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "cstring"

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
        depth_buffer[i] = Z_FAR;
}

void Rasterizer::upload_texture() const
{
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Rasterizer::draw_triangle(Vertex v1, Vertex v2, Vertex v3, Mat4 &transfo)
{

    v1.position = (transfo * Vec4{v1.position, 1}).xyz;
    v2.position = (transfo * Vec4{v2.position, 1}).xyz;
    v3.position = (transfo * Vec4{v3.position, 1}).xyz;

    get_viewport_pos(v1.position);
    get_viewport_pos(v2.position);
    get_viewport_pos(v3.position);

    Vec3 vec1 {v2.position.x - v1.position.x, v2.position.y - v1.position.y, 0};
    Vec3 vec2 {v3.position.x - v1.position.x, v3.position.y - v1.position.y, 0};

    float xMin = min(min(v1.position.x, v2.position.x), v3.position.x);
    float xMax = max(max(v1.position.x, v2.position.x), v3.position.x);
    float yMin = min(min(v1.position.y, v2.position.y), v3.position.y);
    float yMax = max(max(v1.position.y, v2.position.y), v3.position.y);

    // TO DO : change the width and the height
    if (xMin < 0)
        xMin = 0;
    if (xMax > m_width)
        xMax = m_width;
    if (yMin < 0)
        yMin = 0;
    if (yMax > m_height)
        yMax = m_height;

    for (float y = yMin; y < yMax; y++)
    {
        for (float x = xMin; x < xMax; x++)
        {
            Vec3 q {x - v1.position.x, y - v1.position.y, 0};
            //AVX
            float w1 = cross_product(q, vec2) / cross_product(vec1, vec2);
            float w2 = cross_product(vec1, q) / cross_product(vec1, vec2);
            float w3 = 1.f - w1 - w2;

            if (w1 >= 0.f && w2 >= 0.f && w1 + w2 <= 1 )
            {
                float z = v1.position.z * w1 + v2.position.z * w2 + v3.position.z * w3;
                set_pixel_color(x, y, z,{v1.color * w1 + v2.color * w2 + v3.color * w3});
            }
        }
    }
}

void Rasterizer::draw_point(Vertex v, Mat4 &transfo)
{
    v.position = (transfo * Vec4{v.position, 1}).xyz;
    get_viewport_pos(v.position);
    set_pixel_color(v.position.x, v.position.y, 0, v.color);
}

void Rasterizer::get_viewport_pos(Vec3 &v)
{
    v.x = (v.x + 1)  * 0.5 * m_width;
    v.y = (v.y + 1)  * 0.5 * m_height;
}

void Rasterizer::set_pixel_color(uint x, uint y, uint z, const Color &c)
{
    if (z < depth_buffer[x + y * m_width])
    {
        color_buffer[x + y * m_width] = c;
        depth_buffer[x + y * m_width] = z;
    }
}