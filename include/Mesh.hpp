#pragma once

#include "Vertex.hpp"
#include <vector>

class Mesh
{
private:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
public:
    Mesh();
    ~Mesh();
    static Mesh* CreateTriangle();
    static Mesh* CreateCube();
    static Mesh* CreateSphere(int latitudeCount, int longitudeCount);

};