#include "Mesh.hpp"
#include "Vec4.hpp"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Mesh *Mesh::CreateCube()
{
}

Mesh *Mesh::CreateSphere(int latitudeCount, int longitudeCount)
{
}

Mesh *Mesh::CreateTriangle()
{
    Mesh *mesh = new Mesh{};
    int width = 20;
    int height = 10;
    Vertex v1 {{0.5, 1, 0}};
    Vertex v2 {{1, 0, 0}};
    Vertex v3 {{-1, 0, 0}};

    mesh->vertices.push_back(v1);   
    mesh->vertices.push_back(v2);   
    mesh->vertices.push_back(v3);   
    
    
    
    for (float y = 0; y < height; y++)
    {
        for(float x = 0; x < width; x++)
        {
            float w1 = ( ( (v2.position.y - v3.position.y) * (x - v3.position.x) ) + ( (v3.position.x - v2.position.x) * (y - v3.position.y) ) ) /
                       ( ( (v2.position.y -v3.position.y) * (v1.position.x - v3.position.x) ) + ( (v3.position.x - v2.position.x) * (v1.position.y - v3.position.y) ) );

            float w2 = ( ( (v3.position.y - v1.position.y) * (x - v3.position.x) ) + ( (v1.position.x - v3.position.x) * (y - v3.position.y) ) ) /
                       ( ( (v2.position.y -v3.position.y) * (v1.position.x - v3.position.x) ) + ( (v3.position.x - v2.position.x) * (v1.position.y - v3.position.y) ) );

            float w3 = 1.f - w1 - w2;
            if (w1 + w2 + w3 == 1)
            {
                float Px = w1 * v1.position.x + w2 * v2.position.x + w3 * v3.position.x;
                float Py = w1 * v1.position.y + w2 * v2.position.y + w3 * v3.position.y;
            }
        
        }
    }
}