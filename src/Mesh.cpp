#include "Mesh.hpp"
#include "Vec4.hpp"
#include <iostream>
#include <cmath>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Mesh *Mesh::CreateCube()
{
}


Mesh *Mesh::CreateTriangle()
{
    Mesh *mesh = new Mesh{};
    
    Vertex v1 {{-1, -1, 0},{255, 0, 0}};
    Vertex v2 {{1, -1, 0},{0, 255, 0}};
    Vertex v3 {{0, 1, 0},{0, 0, 255}};

    mesh->vertices.push_back(v1);   
    mesh->vertices.push_back(v2);   
    mesh->vertices.push_back(v3);
    
    mesh->indices.push_back(0);
    mesh->indices.push_back(1);
    mesh->indices.push_back(2);

    return mesh;
    
}

Mesh *Mesh::CreateSphere(int l, int L)
{
    Mesh *mesh = new Mesh{};


    for (float i = 0; i < l; i++)
    {
        for (float j = 0; j < L + 1; j++)
        {
            float r = sin(i * M_PI / l);
            mesh->vertices.push_back(Vertex{{cosf(j * (M_PI * 2) / L) * r, cosf(i * M_PI / l), sinf(j * (M_PI * 2) / L) * r}, {255, 0 ,0}});
            // mesh->indices.push_back(i + j * l);
            // mesh->indices.push_back(1 + i + j * l);
            // mesh->indices.push_back(i + L + 1 + j * l);
        }    
    }
    mesh->vertices.push_back({{0, -1, 0},{255, 0 ,0}});

    unsigned int i_max = mesh->vertices.size() - 1;
    
    
    for (float i = 0; i < i_max; i++)
    {
        int index = i + L + 1 > i_max ? i_max : i + L + 1;
        int index2 = i + L > i_max ? i_max : i + L;
        mesh->indices.push_back(i);
        mesh->indices.push_back(1 + i);
        mesh->indices.push_back(index);
        
        mesh->indices.push_back(i);
        mesh->indices.push_back(index2);
        mesh->indices.push_back(index);           
    }

    // mesh->vertices.push_back({{0, -1, 0},{255, 0 ,0}});
    // mesh->indices.push_back(mesh->vertices.size());

    return mesh;
}