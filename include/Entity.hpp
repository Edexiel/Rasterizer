#pragma once
#include "Mesh.hpp"
#include "Mat4.hpp"
#include "math.hpp"

class Entity
{
private:
    DRAW_MODE draw_mode;
public:
    Mesh *mesh;
    Mat4 transfo;

    Entity();
    Entity(Mesh* _mesh);
    Entity(Mesh* mesh, Mat4 transfo);
    ~Entity();

    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);

    void setDrawMode(DRAW_MODE d_m);
    DRAW_MODE getDrawMode();

    void update(double deltaTime);
    void draw(double deltaTime);
};
