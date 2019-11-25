#include <iostream>
#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
// #include "cmath"
#include "math.hpp"

Rasterizer::Rasterizer(uint *width, uint *height) : m_width{width}, m_height{height}, render_target{*width, *height} {}
Rasterizer::~Rasterizer() {}

void Rasterizer::render_scene(Scene *pScene)
{
    //set the color in black
    for (Entity &e : pScene->entities)
    {

        switch (TRIANGLE)
        {
        case POINT:
        {
            for (uint i = 0; i < e.mesh->indices.size(); i++)
                draw_point(e.mesh->vertices[i]);
            break;
        }
        case TRIANGLE:
        {
            if (e.mesh->indices.size() < 3)
                break;

            for (uint i = 0; i < e.mesh->indices.size() - 2; i += 3)
                draw_triangle(e.mesh->vertices[i], e.mesh->vertices[i + 1], e.mesh->vertices[i + 2]);
            break;
        }

        default:
            break;
        }
    }

    { // Render target
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, render_target.getTextureName());
        render_target.uploadTexture();
        render_target.clearBuffer();

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
}

void Rasterizer::draw_triangle(Vertex &v1, Vertex &v2, Vertex &v3, Texture &pTarget, uint width, uint height)
{

    float xMin = min(min(v1.position.x, v2.position.x), v3.position.x);
    float xMax = max(max(v1.position.x, v2.position.x), v3.position.x);
    float yMin = min(min(v1.position.y, v2.position.y), v3.position.y);
    float yMax = max(max(v1.position.y, v2.position.y), v3.position.y);

    // TO DO : change the width and the height
    if (xMin < 0)
        xMin = 0;
    if (xMax > width)
        xMax = 0; //width ?
    if (yMin < 0)
        yMin = 0;
    if (yMax > height)
        yMax = 0; //height ?

    for (float y = yMin; y < yMax; y++)
    {
        for (float x = xMin; x < xMax; x++)
        {
            //AVX
            float w1 = (((v2.position.y - v3.position.y) * (x - v3.position.x)) + ((v3.position.x - v2.position.x) * (y - v3.position.y))) /
                       (((v2.position.y - v3.position.y) * (v1.position.x - v3.position.x)) + ((v3.position.x - v2.position.x) * (v1.position.y - v3.position.y)));

            float w2 = (((v3.position.y - v1.position.y) * (x - v3.position.x)) + ((v1.position.x - v3.position.x) * (y - v3.position.y))) /
                       (((v2.position.y - v3.position.y) * (v1.position.x - v3.position.x)) + ((v3.position.x - v2.position.x) * (v1.position.y - v3.position.y)));

            float w3 = 1.f - w1 - w2;

            //if (fabs((w1 + w2 + w3) - 1) == 0)
            if (w1 >= 0.f && w2 >= 0.f && w3 >= 0.0005f)
                pTarget.SetPixelColor(x, y, {v1.color * w1 + v2.color * w2 + v3.color * w3});
        }
    }
}

void Rasterizer::draw_point(Vertex &v, Texture &t)
{
    t.SetPixelColor(v.position.x, v.position.y, v.color);
}

void Rasterizer::draw_triangle(Vertex &v1, Vertex &v2, Vertex &v3)
{
    draw_triangle(v1, v2, v3, render_target, *m_width, *m_height);
}

void Rasterizer::draw_point(Vertex &v)
{
    draw_point(v, render_target);
}