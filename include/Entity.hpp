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
    Entity(Mesh* mesh, Mat4& transfo);
    ~Entity();
};

