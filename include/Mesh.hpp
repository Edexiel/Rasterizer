#pragma once

#include "Vertex.hpp"
#include <vector>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    Mesh();
    ~Mesh();
    static Mesh* CreateTriangle();
    static Mesh* CreateCube();
    static Mesh* CreateSphere(int latitudeCount, int longitudeCount);
};