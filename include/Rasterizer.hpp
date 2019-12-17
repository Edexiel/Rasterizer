#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include "Texture.hpp"
#include "Scene.hpp"
#include "light.hpp"
#include "Vertex.hpp"
#include <cstring>
#include <thread>

class Rasterizer
{
private:
    uint m_width;
    uint m_height;

    Color *color_buffer;
    float *depth_buffer;

    GLuint color_buffer_texture;

    void draw_triangle(const Vertex *vertices, const Mat4 &model, const Light &light, const Vec2f *UV, Texture texture);
    void raster_triangle(const Vertex *vertices, const Vec4 *t_vertices, const Vec4 *p_vertices, const Vec4 *t_normals, const Light &light, const Vec2f *UV, Texture texture);

    void draw_line(const Vertex *vertices, const Mat4 &model);
    void raster_line(const Vertex* vertex, const Vec4* vec);

    void draw_point(Vertex v1, Mat4 &transfo);
    void set_pixel_color(uint x, uint y, float z, const Color &c);
    void upload_texture() const;

public:
    Rasterizer(uint width, uint height);

    Mat4 projection;
    Mat4 viewport;
    Mat4 view;

    void draw_scene();
    void render_scene(Scene *pScene);
    void clear_color_buffer();
    void clear_depth_buffer();
};

/**
 * @brief Entry point of the rasterization of a triangle 
 * 
 * @param vertices 
 * @param transformation 
 * @param light 
 */
inline void Rasterizer::draw_triangle(const Vertex *vertices, const Mat4 &transformation, const Light &light, const Vec2f *UV, Texture texture)
{
    // transform space: transformation * vec3      (4D)
    // clipSpace:            transformation * vec3 (4D) [-w,w]
    //      clipping out of bound triangles (0001 0010 0100)
    // NDC:  vec3/vec4.w                          (3D) [-1,1]
    //      Back face culling
    // Screen coordinate : viewport * ndc        (2D)

    Vec4 transCoord[3];
    Vec4 transNorm[3];
    for (int i = 0; i < 3; i++)
    {
        transCoord[i] = view * transformation * (Vec4){vertices[i].position, 1.f};
        transNorm[i] = transformation * (Vec4){vertices[i].normal, 0.f};
    }

    Vec4 clipCoord[3];
    for (short i = 0; i < 3; i++)
        clipCoord[i] = projection * transCoord[i];

    //clipping
    if ((clipCoord[0].x < -clipCoord[0].w || clipCoord[0].x > clipCoord[0].w || clipCoord[0].y < -clipCoord[0].w || clipCoord[0].y > clipCoord[0].w || clipCoord[0].z < -clipCoord[0].w || clipCoord[0].z > clipCoord[0].w) && (clipCoord[1].x < -clipCoord[1].w || clipCoord[1].x > clipCoord[1].w || clipCoord[1].y < -clipCoord[1].w || clipCoord[1].y > clipCoord[1].w || clipCoord[1].z < -clipCoord[1].w || clipCoord[1].z > clipCoord[1].w) && (clipCoord[2].x < -clipCoord[2].w || clipCoord[2].x > clipCoord[2].w || clipCoord[2].y < -clipCoord[2].w || clipCoord[2].y > clipCoord[2].w || clipCoord[2].z < -clipCoord[2].w || clipCoord[2].z > clipCoord[2].w))
        return;

    Vec3 ndc[3];
    for (int i = 0; i < 3; i++)
        ndc[i] = Vec4::homogenize(clipCoord[i]);

    // back face culling
    if (Vec3::cross_product_z(ndc[1] - ndc[0], ndc[2] - ndc[0]) <= 0.f)
        return;

    Vertex screenCoord[3];
    for (int i = 0; i < 3; i++)
        screenCoord[i] = (Vertex){(viewport * (Vec4){ndc[i], 1.f}).xyz, vertices[i].color, vertices[i].normal};

    raster_triangle(screenCoord, transCoord, clipCoord, transNorm, light, UV, texture);
}

/**
 * @brief Rasterization function of the program
 * 
 * @param vertices      screen-tranformed vertices
 * @param t_vetices     object matrix only tranformed vertices
 * @param t_normals     object matric only transformed normals
 * @param light         light source to use
 */
inline void Rasterizer::raster_triangle(const Vertex *vertices, const Vec4 *t_vertices, const Vec4 *p_vertices, const Vec4 *t_normals, const Light &light, const Vec2f *UV, Texture texture)
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

    Vec3 weight {0,0,0};

    for (int y = yMin; y <= yMax; ++y)
    {
        for (int x = xMin; x <= xMax; ++x)
        {
            const Vec3 q{x - v1.position.x, y - v1.position.y, 0};

            weight.y = Vec3::cross_product_z(q, vec2) / Vec3::cross_product_z(vec1, vec2);
            weight.z = Vec3::cross_product_z(vec1, q) / Vec3::cross_product_z(vec1, vec2);

            if (weight.y >= 0.f && weight.z >= 0.f && weight.y + weight.z <= 1)
            {
                weight.x = 1.f - weight.y - weight.z;

                const float z =  Vec3::dot_product({v1.position.z,v2.position.z,v3.position.z},weight); 

                weight.x /= p_vertices[0].w;
                weight.y /= p_vertices[1].w;
                weight.z /= p_vertices[2].w;

                weight = weight * (1/(weight.x+weight.y+weight.z));

                if (z <= depth_buffer[x + y * m_width])
                {

                    const Vec3 t_pos{t_vertices[0].xyz * weight.x + t_vertices[1].xyz * weight.y + t_vertices[2].xyz * weight.z};
                    const Vec3 t_normal{t_normals[0].xyz * weight.x + t_normals[1].xyz * weight.y + t_normals[2].xyz * weight.z};

                    Color t_color{v1.color * weight.x + v2.color * weight.y + v3.color * weight.z};
#if 0 //Cheap wireframe
                    if (min(min(weight.x, weight.y), weight.z) < 0.016f)
                    {
                        set_pixel_color(x, y, z, {(unsigned char)(255), (unsigned char)(255), (unsigned char)(255)});
                    }
                    else
                    {
                        set_pixel_color(x, y, z, t_color);
                    }
#else
                    if(texture.texture != nullptr || UV != nullptr)
                    {
                        const Vec2f c_uv { UV[0].x * weight.x + UV[1].x * weight.y + UV[2].x * weight.z,UV[0].y * weight.x + UV[1].y * weight.y + UV[2].y * weight.z};
                        Color pixelTexture = texture.accessor(c_uv.x, c_uv.y);
                        light.apply_light(t_pos, t_normal, pixelTexture, light.camera_pos, light.light_pos);
                        set_pixel_color(x, y, z, pixelTexture);
                    }
                    else
                    {
                        light.apply_light(t_pos, t_normal, t_color, light.camera_pos, light.light_pos);
                        set_pixel_color(x, y, z, t_color);
                    }
                        
#endif
                }
            }
        }
    }
}



inline void Rasterizer::draw_line(const Vertex *vertices, const Mat4 &transformation)
{
    // transform space: transformation * vec3      (4D)
    // clipSpace:            transformation * vec3 (4D) [-w,w]
    //      clipping out of bound triangles (0001 0010 0100)
    // NDC:  vec3/vec4.w                          (3D) [-1,1]
    //      Back face culling
    // Screen coordinate : viewport * ndc        (2D)

    Vec4 transCoord[2];
    for (int i = 0; i < 2; i++)
    {
        transCoord[i] = view * transformation * (Vec4){vertices[i].position, 1.f};
    }

    Vec4 clipCoord[2];
    for (short i = 0; i < 2; i++)
        clipCoord[i] = projection * transCoord[i];

    //clipping
    if ((clipCoord[0].x < -clipCoord[0].w || clipCoord[0].x > clipCoord[0].w || clipCoord[0].y < -clipCoord[0].w || clipCoord[0].y > clipCoord[0].w || clipCoord[0].z < -clipCoord[0].w || clipCoord[0].z > clipCoord[0].w) && (clipCoord[1].x < -clipCoord[1].w || clipCoord[1].x > clipCoord[1].w || clipCoord[1].y < -clipCoord[1].w || clipCoord[1].y > clipCoord[1].w || clipCoord[1].z < -clipCoord[1].w || clipCoord[1].z > clipCoord[1].w))
        return;

    Vec3 ndc[2];
    for (int i = 0; i < 2; i++)
        ndc[i] = Vec4::homogenize(clipCoord[i]);

    // back face culling
    // if (Vec3::cross_product_z(ndc[1], ndc[0]) <= 0.f)
    //     return;

    Vertex screenCoord[2];
    for (int i = 0; i < 2; i++)
        screenCoord[i] = (Vertex){(viewport * (Vec4){ndc[i], 1.f}).xyz, vertices[i].color, vertices[i].normal};

    raster_line(screenCoord, transCoord);
}

inline void Rasterizer::raster_line(const Vertex* vertex, const Vec4* vec)
{
    Vertex v1 = vertex[0];
    Vertex v2 = vertex[1];

    if (v1.position.x > m_width)
        v1.position.x = m_width;
    else if (v1.position.x < 0)
        v1.position.x = 0;

    if (v1.position.y > m_height)
        v1.position.y = m_height;
    else if (v1.position.y < 0)
        v1.position.y = 0;

    if (v2.position.x > m_width)
        v2.position.x = m_width;
    else if (v2.position.x < 0)
        v2.position.x = 0;

    if (v2.position.y > m_height)
        v2.position.y = m_height;
    else if (v2.position.y < 0)
        v2.position.y = 0;

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

    int maxX = (int)v2.position.x;


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

inline void Rasterizer::clear_color_buffer()
{
#pragma omp parallel for
    for (size_t i = 0; i < m_height; i++)
        memset(&color_buffer[m_width * i], 0xDF, m_width * sizeof(Color));

    // const uint size = m_width * m_height;
    // #pragma omp parallel for simd
    //     for (size_t i = 0; i < size; i++)
    //         color_buffer[i] = {255, 255, 255};

    // intrin_ZERO_float((float*)color_buffer,m_width * m_height);
}
inline void Rasterizer::clear_depth_buffer()
{
    const uint size = m_width * m_height;

    for (size_t i = 0; i < size; i++)
    {
        depth_buffer[i] = 10.f;
    }
}

inline void Rasterizer::draw_scene()
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

inline void Rasterizer::upload_texture() const
{
    glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

inline void Rasterizer::set_pixel_color(uint x, uint y, float z, const Color &c)
{
    // std::cout << z << std::endl;
    const uint index = x + y * m_width;

    color_buffer[index] = c;
    depth_buffer[index] = z;
}
