#include "Mesh.hpp"
#include "Vec4.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <cmath>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh *Mesh::CreateCube(char *filename)
{
    Vec2f topLeft{0, 0};
    Vec2f topRight{1, 0};
    Vec2f bottomLeft{0, 1};
    Vec2f bottomRight{1, 1};

    Mesh *mesh = new Mesh{};
    mesh->texture.load_PNG(filename);

    Color color{255, 0, 0};
    mesh->vertices.push_back(Vertex{{-0.5, -0.5, 0.5}, color});
    mesh->vertices.push_back(Vertex{{0.5, -0.5, 0.5}, color});
    mesh->vertices.push_back(Vertex{{-0.5, -0.5, -0.5}, color});
    mesh->vertices.push_back(Vertex{{0.5, -0.5, -0.5}, color});
    mesh->vertices.push_back(Vertex{{0.5, 0.5, -0.5}, color});
    mesh->vertices.push_back(Vertex{{0.5, 0.5, 0.5}, color});
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, 0.5}, color});
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, -0.5}, color});

    for (uint i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->vertices[i].normal = Vec3::normalize(mesh->vertices[i].position);
    }

    //down
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomRight);
    mesh->indices.push_back(2);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(2);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(3);
    mesh->UV.push_back(topLeft);

    //right side
    mesh->indices.push_back(3);
    mesh->UV.push_back(bottomRight);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topLeft);

    //front
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomRight);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topLeft);

    //left side
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomRight);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topLeft);

    //back
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomRight);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topLeft);
    mesh->indices.push_back(3);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomRight);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topLeft);

    //top
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topLeft);
    mesh->indices.push_back(6);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight);
    mesh->indices.push_back(6);
    mesh->UV.push_back(bottomLeft);
    mesh->indices.push_back(5);
    mesh->UV.push_back(bottomRight);

    return mesh;
}

Mesh *Mesh::CreateTriangle()
{
    Mesh *mesh = new Mesh{};

    Vertex v1{{0, 1, 0}, {255, 255, 255}};
    Vertex v2{{1, -1, 0}, {255, 255, 255}};
    Vertex v3{{-1, -1, 0}, {255, 255, 255}};

    mesh->vertices.push_back(v1);
    mesh->vertices.push_back(v2);
    mesh->vertices.push_back(v3);

    for (uint i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->vertices[i].normal = Vec3::normalize(mesh->vertices[i].position);
    }

    mesh->indices.push_back(0);
    mesh->indices.push_back(1);
    mesh->indices.push_back(2);

    return mesh;
}

Mesh *Mesh::CreateSphere(int l, int L)
{
    Mesh *mesh = new Mesh{};

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < L + 1; j++)
        {
            float r = sinf(i * (float)M_PI / (float)l);
            mesh->vertices.push_back(Vertex{{cosf(j * ((float)M_PI * 2) / (float)L) * r, cosf(i * (float)M_PI / (float)l), sinf(j * ((float)M_PI * 2) / (float)L) * r}, {255, 255, 255}});
        }
    }
    mesh->vertices.push_back({{0, -1, 0}, {255, 255, 255}});

    unsigned int i_max = mesh->vertices.size() - 1;

    for (uint i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->vertices[i].normal = Vec3::normalize(mesh->vertices[i].position);
    }

    for (uint i = 0; i < i_max; i++)
    {
        uint index = i + L + 1 > i_max ? i_max : i + L + 1;
        uint index2 = i + L > i_max ? i_max : i + L;
        mesh->indices.push_back(i);
        mesh->indices.push_back(1 + i);
        mesh->indices.push_back(index);

        mesh->indices.push_back(index2);
        mesh->indices.push_back(i);
        mesh->indices.push_back(index);
    }

    return mesh;
}

Mesh *Mesh::CreateVectorLight(float x, float y, float z)
{
    Mesh *mesh = new Mesh{};
    mesh->vertices.push_back(Vertex{{x, y, z}, {255, 0, 0}});
    mesh->vertices.push_back(Vertex{{0, 0, 0}, {0, 0, 0}});
    mesh->indices.push_back(0);
    mesh->indices.push_back(1);

    return mesh;
}

Mesh *Mesh::LoadObj(char *path)
{
    Mesh *object = new Mesh{};

    bool hasNormals = false;
    bool hasColors = false;

    std::string warn;
    std::string err;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;

    tinyobj::LoadObj(&attrib, &shapes, NULL, &warn, &err, path, NULL, true);

    if (!err.empty())
        std::cout << "Error loading obj: " << err.c_str() << std::endl;
    if (!warn.empty())
        std::cout << "Warning loading obj: " << warn.c_str() << std::endl;

    hasNormals = !attrib.normals.empty();
    hasColors = !attrib.colors.empty();

    for (uint i = 0; i < attrib.vertices.size() - 3; i += 3)
    {
        Vertex v{};

        v.position = {(float)attrib.vertices[i],
                      (float)attrib.vertices[i + 1],
                      (float)attrib.vertices[i + 2]};

        v.normal = hasNormals ? Vec3{(float)attrib.normals[i],
                                     (float)attrib.normals[i + 1],
                                     (float)attrib.normals[i + 2]}
                              : Vec3{0.f, 0.f, 0.f};

        v.color = hasColors ? Color{(unsigned char)clamp((float)attrib.colors[i] * 255,0.f,255.f),
                                    (unsigned char)clamp((float)attrib.colors[i + 1] * 255,0.f,255.f),
                                    (unsigned char)clamp((float)attrib.colors[i + 2] * 255,0.f,255.f)}
                            : Color{255, 255, 255};

        object->vertices.push_back(v);
    }

    for (tinyobj::shape_t &shape : shapes)
    {
        
        for (tinyobj::index_t &index : shape.mesh.indices)
        {
            object->indices.push_back(index.vertex_index);
        }
    }

    return object;
}