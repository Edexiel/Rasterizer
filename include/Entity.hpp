#pragma once 
#include "Mesh.hpp"
#include "Mat4.hpp"


class Entity
{
private:

public:
    Mesh* mesh;
    Mat4 transfo;
    Entity();
    Entity(Mesh* _mesh);
    Entity(Mesh* mesh, Mat4 transfo);
    ~Entity();

    // void scale(float x);
    // void translate();
    // void rotate();
};

