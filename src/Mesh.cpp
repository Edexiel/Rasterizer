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
    
    Vertex v1 {{0.5, 1, 0},{255, 0, 0}};
    Vertex v2 {{1, -1, 0},{0, 255, 0}};
    Vertex v3 {{-1, -1, 0},{0, 0, 255}};

    mesh->vertices.push_back(v1);   
    mesh->vertices.push_back(v2);   
    mesh->vertices.push_back(v3);
    
    mesh->indices.push_back(0);
    mesh->indices.push_back(1);
    mesh->indices.push_back(2);

    return mesh;
    
}