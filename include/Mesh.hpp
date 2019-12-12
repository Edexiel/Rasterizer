#pragma once

#include "Vertex.hpp"
#include "Vec2.hpp"
#include <vector>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::vector<Vec2> UV;
    // std::vector<Vec3> normals;
    static Mesh* CreateTriangle();
    static Mesh* CreateCube();
    static Mesh* CreateSphere(int latitudeCount, int longitudeCount);
    static Mesh* CreateVectorLight(float x, float y, float z);
    void         CreateNormals();
};