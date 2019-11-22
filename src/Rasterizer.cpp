#include "Rasterizer.hpp"
#include "Scene.hpp"
#include "Vertex.hpp"
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
            case POINT :
            for(int i = 0; i < e.mesh->indices.size() - 2; i + 3)
                render_triangle(e.mesh->vertices[i], e.mesh->vertices[i + 1], e.mesh->vertices[i + 2], pTarget);
                break;
            case TRIANGLE : 
            for(int i = 0; i <  e.mesh->indices.size(); i++)
                render_point(e.mesh->vertices[i], pTarget);
                break;

            default :
                break;
        }

    }
}

void Rasterizer::render_triangle(Vertex& v1, Vertex& v2, Vertex& v3, Texture *pTarget)
{
    int width = 20;
    int height = 10;

    for (float y = 0; y < height; y++)
    {
        for (float x = 0; x < width; x++)
        {
            float w1 = (((v2.position.y - v3.position.y) * (x - v3.position.x)) + ((v3.position.x - v2.position.x) * (y - v3.position.y))) /
                       (((v2.position.y - v3.position.y) * (v1.position.x - v3.position.x)) + ((v3.position.x - v2.position.x) * (v1.position.y - v3.position.y)));

            float w2 = (((v3.position.y - v1.position.y) * (x - v3.position.x)) + ((v1.position.x - v3.position.x) * (y - v3.position.y))) /
                       (((v2.position.y - v3.position.y) * (v1.position.x - v3.position.x)) + ((v3.position.x - v2.position.x) * (v1.position.y - v3.position.y)));

            float w3 = 1.f - w1 - w2;
            if (w1 + w2 + w3 == 1)
            {
                // float Px = w1 * v1.position.x + w2 * v2.position.x + w3 * v3.position.x;
                // float Py = w1 * v1.position.y + w2 * v2.position.y + w3 * v3.position.y;
            }
        }
    }
}

void Rasterizer::render_point(Vertex& v1, Texture *pTarget)
{
    
}