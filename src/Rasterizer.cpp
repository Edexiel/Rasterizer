#include <iostream>
#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
#include "cmath"

Rasterizer::Rasterizer()
{
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::render_scene(Scene *pScene, Texture *pTarget)
{
    //set the color in black
    for (Entity &e : pScene->entities)
    {
        if (e.mesh->indices.size() < 3)
            return;

        switch (POINT)
        {
        case POINT:
            for (int i = 0; i < e.mesh->indices.size(); i++)
                render_point(e.mesh->vertices[i], pTarget);

            break;
        case TRIANGLE:
            for (int i = 0; i < e.mesh->indices.size() - 2; i + 3)
                render_triangle(e.mesh->vertices[i], e.mesh->vertices[i + 1], e.mesh->vertices[i + 2], pTarget);

            break;

        default:
            break;
        }
    }
}

void Rasterizer::render_triangle(Vertex &v1, Vertex &v2, Vertex &v3, Texture *pTarget)
{

    float xMin = find_x_min_triangle(v1, v2, v3);
    float xMax = find_x_max_triangle(v1, v2, v3);
    float yMin = find_y_min_triangle(v1, v2, v3);
    float yMax = find_y_max_triangle(v1, v2, v3);


    // TO DO : change the width and the height
    if (xMin < 0)
        xMin = 0;
    if(xMax > 800)
        xMax = 0;
    if (yMin < 0)
        yMin = 0;
    if(yMax > 600)
        yMax = 0;

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
            {
                // you can optimize color
                // float Px = v1.position.x * w1 + v2.position.x * w2 + v3.position.x * w3;
                // float Py = v1.position.y * w1 + v2.position.y * w2 + v3.position.y * w3;

                pTarget->SetPixelColor(x, y, {v1.color * w1 + v2.color * w2 + v3.color * w3});
                // std::cout << "x = " << Px << "||" << " y = " << Py<< std::endl;
            }
        }
    }
}

void Rasterizer::render_point(Vertex &v1, Texture *pTarget)
{
    pTarget->SetPixelColor(v1.position.x, v1.position.y, v1.color);
}

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}


float Rasterizer::find_x_max_triangle(Vertex &v1, Vertex &v2, Vertex &v3)
{
    return max(max(v1.position.x, v2.position.x), v3.position.x);
}
float Rasterizer::find_x_min_triangle(Vertex &v1, Vertex &v2, Vertex &v3)
{
    return min(min(v1.position.x, v2.position.x), v3.position.x);
}
float Rasterizer::find_y_max_triangle(Vertex &v1, Vertex &v2, Vertex &v3)
{
    return max(max(v1.position.y, v2.position.y), v3.position.y);
}
float Rasterizer::find_y_min_triangle(Vertex &v1, Vertex &v2, Vertex &v3)
{
    return min(min(v1.position.y, v2.position.y), v3.position.y);
}