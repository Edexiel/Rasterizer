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

    void draw_triangle(const Vertex *vertices, const Mat4 &model, const Light &light, const Vec2f *UV);
    void raster_triangle(const Vertex *vertices, const Vec4 *t_vertices, const Vec4 *p_vertices, const Vec4 *t_normals, const Light &light, const Vec2f *UV);

    void draw_line(Vertex v1, Vertex v2, Mat4 &transfo);
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
inline void Rasterizer::draw_triangle(const Vertex *vertices, const Mat4 &transformation, const Light &light, const Vec2f *UV)
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
        // transNorm[i] = view * transformation * (Vec4){vertices[i].normal, 0.f};
        transNorm[i] = transformation * (Vec4){vertices[i].normal, 0.f};
    }

    Vec4 clipCoord[3];
    for (short i = 0; i < 3; i++)
        clipCoord[i] = projection * transCoord[i];

    if ((clipCoord[0].x < -clipCoord[0].w || clipCoord[0].x > clipCoord[0].w || clipCoord[0].y < -clipCoord[0].w || clipCoord[0].y > clipCoord[0].w || clipCoord[0].z < -clipCoord[0].w || clipCoord[0].z > clipCoord[0].w) && (clipCoord[1].x < -clipCoord[1].w || clipCoord[1].x > clipCoord[1].w || clipCoord[1].y < -clipCoord[1].w || clipCoord[1].y > clipCoord[1].w || clipCoord[1].z < -clipCoord[1].w || clipCoord[1].z > clipCoord[1].w) && (clipCoord[2].x < -clipCoord[2].w || clipCoord[2].x > clipCoord[2].w || clipCoord[2].y < -clipCoord[2].w || clipCoord[2].y > clipCoord[2].w || clipCoord[2].z < -clipCoord[2].w || clipCoord[2].z > clipCoord[2].w))
        return;

    // Ne plus utiliser les clip coord a partir de ce point, elles ont ete homogeneisees
    // opti l'appel de la fonciton homogenize
    Vec3 ndc[3];
    for (int i = 0; i < 3; i++)
        ndc[i] = Vec4::homogenize(clipCoord[i]);

    // back face culling
    // if (Vec3::cross_product_z(ndc[1] - ndc[0], ndc[2] - ndc[0]) <= 0.f)
    //     return;

    Vertex screenCoord[3];
    for (int i = 0; i < 3; i++)
        screenCoord[i] = (Vertex){(viewport * (Vec4){ndc[i], 1.f}).xyz, vertices[i].color, vertices[i].normal};

    raster_triangle(screenCoord, transCoord, clipCoord, transNorm, light, UV);
}

/**
 * @brief Rasterization function of the program
 * 
 * @param vertices      screen-tranformed vertices
 * @param t_vetices     object matrix only tranformed vertices
 * @param t_normals     object matric only transformed normals
 * @param light         light source to use
 */
inline void Rasterizer::raster_triangle(const Vertex *vertices, const Vec4 *t_vertices, const Vec4 *p_vertices, const Vec4 *t_normals, const Light &light, const Vec2f *UV)
{
    // Test texture
    // Texture texture{"media/cratetex.png"};
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

    for (int y = yMin; y <= yMax; ++y)
    {
        for (int x = xMin; x <= xMax; ++x)
        {
            const Vec3 q{x - v1.position.x, y - v1.position.y, 0};

            const float w2 = Vec3::cross_product_z(q, vec2) / Vec3::cross_product_z(vec1, vec2);
            const float w3 = Vec3::cross_product_z(vec1, q) / Vec3::cross_product_z(vec1, vec2);

            if (w2 >= 0.f && w3 >= 0.f && w2 + w3 <= 1)
            {
                const float w1 = 1.f - w2 - w3;
                const float z = v1.position.z * w1 + v2.position.z * w2 + v3.position.z * w3;

                if (z <= depth_buffer[x + y * m_width])
                {

                    const Vec3 t_pos{t_vertices[0].xyz * w1 + t_vertices[1].xyz * w2 + t_vertices[2].xyz * w3};
                    const Vec3 t_normal{t_normals[0].xyz * w1 + t_normals[1].xyz * w2 + t_normals[2].xyz * w3};

                    Color t_color{v1.color * w1 + v2.color * w2 + v3.color * w3};

                    light.apply_light(t_pos, t_normal, t_color, light.camera_pos, light.light_pos);
#if 0 //Cheap wireframe
                    if (min(min(w1, w2), w3) < 0.016f)
                    {
                        set_pixel_color(x, y, z, {(unsigned char)(255), (unsigned char)(255), (unsigned char)(255)});
                    }
                    else
                    {
                        set_pixel_color(x, y, z, t_color);
                    }
#else
                    // float h_w1 = 1;
                    // float h_w2 = 1;
                    // float h_w3 = 1;

                    // if (p_vertices[0].w != 0 || w1 != 0)
                    //     h_w1 = -1 * w1 / p_vertices[0].w;
                    // if (p_vertices[1].w != 0 || w2 != 0)
                    //     h_w2 = -1 * w2 / p_vertices[1].w;
                    // if (p_vertices[2].w != 0 || w3 != 0)
                    //     h_w3 = -1 * w3 / p_vertices[2].w;

                    // float _x = UV[0].x * h_w1 + UV[1].x * h_w2 + UV[2].x * h_w3;
                    // float _y = UV[0].y * h_w1 + UV[1].y * h_w2 + UV[2].y * h_w3;

                    // set_pixel_color(x, y, z, texture.accessor(_x, _y));
                    set_pixel_color(x, y, z, t_color);
#endif
                }
            }
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
#pragma omp parallel for simd
    for (size_t i = 0; i < size; i++)
        depth_buffer[i] = 1.1f;
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
