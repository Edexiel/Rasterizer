#include <iostream>
#include <cstring>
#include <cmath>

#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"
#include "math.hpp"
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
}
void Rasterizer::clear_depth_buffer()
{
    // memset(color_buffer, 0xFF, m_width * m_height * sizeof(unsigned int));
    for (size_t i = 0; i < m_width * m_height; i++)
        depth_buffer[i] = 1.1f;
}

void Rasterizer::upload_texture() const
{
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Rasterizer::raster_triangle(Vertex (&vertices)[3])
{
    // shortcuts
    Vertex &v1 = vertices[0];
    Vertex &v2 = vertices[1];
    Vertex &v3 = vertices[2];

    int xMin = (int)min(min(v1.position.x, v2.position.x), v3.position.x);
    int xMax = (int)max(max(v1.position.x, v2.position.x), v3.position.x);
    int yMin = (int)min(min(v1.position.y, v2.position.y), v3.position.y);
    int yMax = (int)max(max(v1.position.y, v2.position.y), v3.position.y);

    if (xMin < 0)
        xMin = 0;
    if ((uint)xMax >= m_width)
        xMax = m_width-1;
    if (yMin < 0)
        yMin = 0;
    if ((uint)yMax >= m_height)
        yMax = m_height-1;

    Vec3 vec1{v2.position.x - v1.position.x, v2.position.y - v1.position.y, 0};
    Vec3 vec2{v3.position.x - v1.position.x, v3.position.y - v1.position.y, 0};

    for (int y = yMin; y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {
            Vec3 q{x - v1.position.x, y - v1.position.y, 0};

            float w2 = Vec3::cross_product_z(q, vec2) / Vec3::cross_product_z(vec1, vec2);
            float w3 = Vec3::cross_product_z(vec1, q) / Vec3::cross_product_z(vec1, vec2);
            float w1 = 1.f - w2 - w3;

            if (w2 >= 0.f && w3 >= 0.f && w2 + w3 <= 1)
            {
                float z = v1.position.z * w1 + v2.position.z * w2 + v3.position.z * w3;
                // if (min(min(w1, w2), w3) < 0.016f)
                // {
                //     set_pixel_color(x, y, z, {(unsigned char)(255), (unsigned char)(255), (unsigned char)(255)});
                // }
                // else
                // {
                // std::cout << "x: " << x << "y: " << y << "z: " << z << std::endl;
                set_pixel_color(x, y, z, {v1.color * w1 + v2.color * w2 + v3.color * w3});
                // }
            }
        }
    }
}

void Rasterizer::draw_triangle(Vertex (&vertices)[3], Mat4 transformation, Light &light)
{
    // clipSpace = projection * modelview * vec3 (4D) [-w,w]
    //      clipping out of bound triangles (0001 0010 0100)
    // NDC = vec3/vec4.w                         (3D) [-1,1]
    //      Back face culling
    // Screen coordinate = viewport * ndc        (2D)

    Vec4 clipCoord[3];
    for (short i = 0; i < 3; i++)
    {
        clipCoord[i] = projection * transformation * (Vec4){vertices[i].position, 1.f};
    }

    // clipping

    // Light per Vertex
    float mult_colors[3];

    for (short i = 0; i < 3; i++)
    {
        mult_colors[i] = light.apply_light((transformation * Vec4 {vertices[i].position, 1}).xyz,vertices[i].normal);
    }

    // Ne plus utiliser les clip coord a partir de ce point, elles ont ete homogeneisees
    Vec3 ndc[3];
    for (short i = 0; i < 3; i++)
    {
        ndc[i] = clipCoord[i].homogenize().xyz;
    }

    // back face culling
    // if(Vec3::cross_product_z(ndc[1] - ndc[0],ndc[2] - ndc[0]) < 0.f )
    // {
    //     std::cout<<"culled" <<std::endl;
    //     return;
    // }

    Vertex screenCoord[3];
    for (short i = 0; i < 3; i++)
    {
        screenCoord[i] = (Vertex){(viewport * (Vec4){ndc[i], 1.f}).xyz, vertices[i].color * mult_colors[i], vertices[i].normal};
    }

    raster_triangle(screenCoord);
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
    uint index = x + y * m_width;
    if (z <= depth_buffer[index])
    {
        color_buffer[index] = c;
        depth_buffer[index] = z;
    }
}