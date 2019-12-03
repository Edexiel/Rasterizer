#pragma once

#include "Vertex.hpp"
#include <vector>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    // std::vector<Vec3> normals;
    Mesh();
    ~Mesh();
    static Mesh* CreateTriangle();
    static Mesh* CreateCube();
    static Mesh* CreateSphere(int latitudeCount, int longitudeCount);
    static Mesh* CreateVectorLight(float x, float y, float z);
    void         CreateNormals();
};