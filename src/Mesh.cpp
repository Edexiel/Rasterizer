#include "Mesh.hpp"
#include "Vec4.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <cmath>

Mesh::Mesh(){}

Mesh::~Mesh(){}

Mesh *Mesh::CreateCube()
{
    Vec3 top {0, 1, 0};
    Vec3 bottom {0, -1, 0};
    Vec3 left {-1, 0, 0};
    Vec3 right {1, 0, 0};
    Vec3 front {0, 0, 1};
    Vec3 back {0, 0, -1};

    Mesh *mesh = new Mesh{};

    mesh->vertices.push_back(Vertex{{-0.5, -0.5, 0.5}, {0xFF, 0xFF, 0xFF}});  //0       
    mesh->vertices.push_back(Vertex{{0.5, -0.5, 0.5}, {0xFF, 0xFF, 0xFF}});   //1   
    mesh->vertices.push_back(Vertex{{-0.5, -0.5, -0.5}, {0xFF, 0xFF, 0xFF}}); //2       
    mesh->vertices.push_back(Vertex{{0.5, -0.5, -0.5}, {0xFF, 0xFF, 0xFF}});  //3       
    mesh->vertices.push_back(Vertex{{0.5, 0.5, -0.5}, {0xFF, 0xFF, 0xFF}});   //4   
    mesh->vertices.push_back(Vertex{{0.5, 0.5, 0.5}, {0xFF, 0xFF, 0xFF}});    //5   
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, 0.5}, {0xFF, 0xFF, 0xFF}});   //6   
    mesh->vertices.push_back(Vertex{{-0.5, 0.5, -0.5}, {0xFF, 0xFF, 0xFF}});  //7       

    for (uint i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->vertices[i].normal = mesh->vertices[i].position.get_normal(); 
    }

    mesh->indices.push_back(0); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(1); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(2); //mesh->normals.push_back(bottom);

    mesh->indices.push_back(1); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(2); //mesh->normals.push_back(bottom);
    mesh->indices.push_back(3); //mesh->normals.push_back(bottom); 

    mesh->indices.push_back(3); //mesh->normals.push_back(right);
    mesh->indices.push_back(4); //mesh->normals.push_back(right);
    mesh->indices.push_back(1); //mesh->normals.push_back(right);

    mesh->indices.push_back(4);//mesh->normals.push_back(right);
    mesh->indices.push_back(1);//mesh->normals.push_back(right);
    mesh->indices.push_back(5);//mesh->normals.push_back(right);

    mesh->indices.push_back(1);//mesh->normals.push_back(front);
    mesh->indices.push_back(5);//mesh->normals.push_back(front);
    mesh->indices.push_back(0);//mesh->normals.push_back(front);

    mesh->indices.push_back(5);//mesh->normals.push_back(front);
    mesh->indices.push_back(0);//mesh->normals.push_back(front);
    mesh->indices.push_back(6);//mesh->normals.push_back(front);

    mesh->indices.push_back(0);//mesh->normals.push_back(left);
    mesh->indices.push_back(6);//mesh->normals.push_back(left);
    mesh->indices.push_back(2);//mesh->normals.push_back(left);

    mesh->indices.push_back(6);//mesh->normals.push_back(left);
    mesh->indices.push_back(2);//mesh->normals.push_back(left);
    mesh->indices.push_back(7);//mesh->normals.push_back(left);

    mesh->indices.push_back(2);//mesh->normals.push_back(back);
    mesh->indices.push_back(7);//mesh->normals.push_back(back);
    mesh->indices.push_back(4);//mesh->normals.push_back(back);

    mesh->indices.push_back(2); //mesh->normals.push_back(back);
    mesh->indices.push_back(3); //mesh->normals.push_back(back);
    mesh->indices.push_back(4); //mesh->normals.push_back(back);

    mesh->indices.push_back(7);//mesh->normals.push_back(top);
    mesh->indices.push_back(4);//mesh->normals.push_back(top);
    mesh->indices.push_back(6);//mesh->normals.push_back(top);

    mesh->indices.push_back(4);//mesh->normals.push_back(top);
    mesh->indices.push_back(6);//mesh->normals.push_back(top);
    mesh->indices.push_back(5); //mesh->normals.push_back(top);

    // mesh->CreateNormals();

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
        mesh->vertices[i].normal = mesh->vertices[i].position.get_normal(); 
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
    mesh->vertices.push_back({{0, -1, 0},{255, 255, 255}});

    unsigned int i_max = mesh->vertices.size() - 1;
    
    for (uint i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->vertices[i].normal = mesh->vertices[i].position.get_normal(); 
    }

    for (uint i = 0; i < i_max; i++)
    {
        uint index = i + L + 1 > i_max ? i_max : i + L + 1;
        uint index2 = i + L > i_max ? i_max : i + L;
        mesh->indices.push_back(i);
        mesh->indices.push_back(1 + i);
        mesh->indices.push_back(index);
        
        mesh->indices.push_back(i);
        mesh->indices.push_back(index2);
        mesh->indices.push_back(index);           
    }

    return mesh;
}

Mesh* Mesh::CreateVectorLight(float x, float y, float z)
{
    Mesh *mesh = new Mesh{};
    mesh->vertices.push_back(Vertex{{x, y, z}, {255, 0, 0}});
    mesh->vertices.push_back(Vertex{{0, 0, 0}, {0, 0, 0}});
    mesh->indices.push_back(0);
    mesh->indices.push_back(1);

    return mesh;
}

// void Mesh::CreateNormals()
// {
//     for(int i = 0; i < indices.size() - 2; i += 3) 
//     {
//         normals.push_back(vector_product(vertices[i + 1].position, vertices[i + 2].position));
//         normals.push_back(vector_product(vertices[i + 2].position, vertices[i].position));
//         normals.push_back(vector_product(vertices[i].position, vertices[i + 1].position));
//     }
// }