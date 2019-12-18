#pragma once

#include "Vertex.hpp"
#include "Vec2.hpp"
#include "Texture.hpp"
#include <vector>

class Mesh
{
private:
public:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::vector<Vec2f> UV;
    
    Texture texture;
    
    static Mesh* CreateTriangle();
    static Mesh* CreateCube(char* filename);
    static Mesh* CreateSphere(int latitudeCount, int longitudeCount);
    static Mesh* CreateVectorLight(float x, float y, float z);
    static Mesh *LoadObj(char *path);
};