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
    Mesh *mesh = new Mesh{};

    mesh->vertices.push_back(Vertex{{-0.5, -0.5, 0.5}, {0xFF,0x00, 0x00}});  // 0
    mesh->vertices.push_back(Vertex{{0.5, -0.5, 0.5}, {0x00, 0xFF, 0x00}});   // 1
    mesh->vertices.push_back(Vertex{{-0.5, -0.5, -0.5}, {0x00, 0x00, 0xFF}}); // 2
    mesh->vertices.push_back(Vertex{{0.5, -0.5, -0.5}, {0xFF, 0x00, 0x00}});  // 3
    mesh->vertices.push_back(Vertex{{0.5, 0.5, -0.5}, {0x00, 0xFF, 0x00}});   // 4
    mesh->vertices.push_back(Vertex{{0.5, 0.5, 0.5}, {0x00, 0x00, 0xFF}});    // 5
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, 0.5}, {0xFF, 0x00, 0x00}});   // 6
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, -0.5}, {0x00, 0xFF, 0x00}});  // 7

    mesh->indices.push_back(0);
    mesh->indices.push_back(1);
    mesh->indices.push_back(2);
    mesh->indices.push_back(3);
    mesh->indices.push_back(4);
    mesh->indices.push_back(1);
    mesh->indices.push_back(5);
    mesh->indices.push_back(0);
    mesh->indices.push_back(6);
    mesh->indices.push_back(2);
    mesh->indices.push_back(7);
    mesh->indices.push_back(4);
    mesh->indices.push_back(6);
    mesh->indices.push_back(5);
}

Mesh *Mesh::CreateSphere(int latitudeCount, int longitudeCount)
{
}

Mesh *Mesh::CreateTriangle()
{
    Mesh *mesh = new Mesh{};

    Vertex v1{{0.5, 1, 0}, {255, 0, 0}};
    Vertex v2{{1, -1, 0}, {0, 255, 0}};
    Vertex v3{{-1, -1, 0}, {0, 0, 255}};

    mesh->vertices.push_back(v1);
    mesh->vertices.push_back(v2);
    mesh->vertices.push_back(v3);

    mesh->indices.push_back(0);
    mesh->indices.push_back(1);
    mesh->indices.push_back(2);

    return mesh;
}