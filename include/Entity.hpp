#pragma once
#include "Mesh.hpp"
#include "Mat4.hpp"
#include "tools.hpp"
#include "Vec3.hpp"

class Entity
{
private:
    DRAW_MODE draw_mode;

public:
    Mesh *mesh;
    Mat4 transfo;

    Entity();
    Entity(Mesh *_mesh);
    Entity(Mesh *mesh, Mat4 transfo);
    ~Entity();

    void scale(const Vec3& scale);
    void translate(const Vec3& translation);
    void rotate(const Vec3& rotation);

    void resetTransformation();

    void setDrawMode(DRAW_MODE d_m);
    DRAW_MODE getDrawMode() const;
};

inline void Entity::setDrawMode(DRAW_MODE d_m)
{
    draw_mode = d_m;
}

inline DRAW_MODE Entity::getDrawMode() const
{
    return draw_mode;
}

