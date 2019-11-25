#include "Mesh.hpp"
#include "Vec4.hpp"
#include <cmath>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Mesh *Mesh::CreateCube()
{
    Mesh *mesh = new Mesh{};

    mesh->vertices.push_back(Vertex{{-0.5, -0.5, 0.5}, {0xFF, 0x00, 0x00}});
    mesh->vertices.push_back(Vertex{{0.5, -0.5, 0.5}, {0x00, 0xFF, 0x00}});
    mesh->vertices.push_back(Vertex{{-0.5, -0.5, -0.5}, {0x00, 0x00, 0xFF}});
    mesh->vertices.push_back(Vertex{{0.5, -0.5, -0.5}, {0xFF, 0x00, 0x00}});
    mesh->vertices.push_back(Vertex{{0.5, 0.5, -0.5}, {0x00, 0xFF, 0x00}});
    mesh->vertices.push_back(Vertex{{0.5, 0.5, 0.5}, {0x00, 0x00, 0xFF}});
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, 0.5}, {0xFF, 0x00, 0x00}});
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, -0.5}, {0x00, 0xFF, 0x00}});

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

    return mesh;
}

// Mesh *Mesh::CreateSphere(int latitudeCount, int longitudeCount)
// {
//         // Mesh *mesh = new Mesh{};

//     // float x, y, z, alpha, beta; // Storage for coordinates and angles
//     // float radius = 1.0f;
//     // int gradation = 32;

//     // for (alpha = 0.0; alpha < M_PI; alpha += M_PI/gradation)
//     // {    
//     //     for (beta = 0.0; beta < 2.00 * M_PI; beta += M_PI/gradation)            
//     //     {            
//     //         x = radius * cos(beta) * sin(alpha);
//     //         y = radius * sin(beta) * sin(alpha);
//     //         z = radius * cos(alpha);
//     //         mesh->vertices.push_back(Vertex{{x, y, z}, {255, 0.0 ,0.0}});
//     //         x = radius * cos(beta) * sin(alpha + M_PI / gradation);
//     //         y = radius * sin(beta) * sin(alpha + M_PI / gradation);
//     //         z = radius * cos(alpha + M_PI / gradation);            
//     //         mesh->vertices.push_back(Vertex{{x, y, z}, {255, 0.0 ,0.0}});


//     //         return mesh;            
//     //     }

//     float y = cosf(i * M_PI / l);
//     float r = sin(i * M_PI / l);
//     float x = cosf(j * (M_PI * 2) / L) * r;
//     float z = sinf(j * (M_PI * 2) / L) * r;
// }

Mesh *Mesh::CreateTriangle()
{
    Mesh *mesh = new Mesh{};

    Vertex v1{{0, 1, 0}, {255, 0, 0}};
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