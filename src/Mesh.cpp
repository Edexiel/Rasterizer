#include "Mesh.hpp"
#include "Vec4.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <cmath>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh *Mesh::CreateCube()
{
    // Vec3 top{0, 1, 0};
    // Vec3 bottom{0, -1, 0};
    // Vec3 left{-1, 0, 0};
    // Vec3 right{1, 0, 0};
    // Vec3 front{0, 0, 1};
    // Vec3 back{0, 0, -1};

    Vec2f topLeft{0, 0};
    Vec2f topRight{1, 0};
    Vec2f bottomLeft{0, 1};
    Vec2f bottomRight{1, 1};

    Mesh *mesh = new Mesh{};
    mesh->texture = nullptr;

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
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(2);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(2);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(3);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(bottom);

    //right side
    mesh->indices.push_back(3);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(right);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(right);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(right);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(right);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(right);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(right);

    //front
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(front);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(front);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(front);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(front);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(front);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(front);

    //left side
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(left);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(left);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(left);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(left);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(left);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(left);

    //back
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(back);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(back);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(back);
    mesh->indices.push_back(3);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(back);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(back);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(back);

    //top
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(top);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(top);
    mesh->indices.push_back(6);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(top);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(top);
    mesh->indices.push_back(6);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(top);
    mesh->indices.push_back(5);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(top);

    return mesh;
}

Mesh *Mesh::CreateCube(char *filename)
{
    // Vec3 top{0, 1, 0};
    // Vec3 bottom{0, -1, 0};
    // Vec3 left{-1, 0, 0};
    // Vec3 right{1, 0, 0};
    // Vec3 front{0, 0, 1};
    // Vec3 back{0, 0, -1};

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
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(2);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(2);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(3);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(bottom);

    //right side
    mesh->indices.push_back(3);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(right);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(right);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(right);
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(right);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(right);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(right);

    //front
    mesh->indices.push_back(1);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(front);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(front);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(front);
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(front);
    mesh->indices.push_back(5);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(front);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(front);

    //left side
    mesh->indices.push_back(0);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(left);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(left);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(left);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(left);
    mesh->indices.push_back(6);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(left);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(left);

    //back
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(back);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(back);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(back);
    mesh->indices.push_back(3);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(back);
    mesh->indices.push_back(2);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(back);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(back);

    //top
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(top);
    mesh->indices.push_back(7);
    mesh->UV.push_back(topLeft); //mesh->normals.push_back(top);
    mesh->indices.push_back(6);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(top);
    mesh->indices.push_back(4);
    mesh->UV.push_back(topRight); //mesh->normals.push_back(top);
    mesh->indices.push_back(6);
    mesh->UV.push_back(bottomLeft); //mesh->normals.push_back(top);
    mesh->indices.push_back(5);
    mesh->UV.push_back(bottomRight); //mesh->normals.push_back(top);

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

    for (const tinyobj::shape_t &shape : shapes)
    {
        for (const tinyobj::index_t &index : shape.mesh.indices)
        {
            Vertex v;
            v.position = {
                attrib.vertices[index.vertex_index * 3 + 0],
                attrib.vertices[index.vertex_index * 3 + 1],
                attrib.vertices[index.vertex_index * 3 + 2]};

            if (hasNormals)
            {
                v.normal = {
                    attrib.normals[index.normal_index * 3 + 0],
                    attrib.normals[index.normal_index * 3 + 1],
                    attrib.normals[index.normal_index * 3 + 2]};
            }

            object->vertices.push_back(v);
        }
    }
}