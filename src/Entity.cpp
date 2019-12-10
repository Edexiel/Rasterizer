#include "Entity.hpp"
#include "string.h"

Entity::Entity() : draw_mode{TRIANGLE}, transfo{Mat4::identity()} {}
Entity::Entity(Mesh *_mesh) : draw_mode{TRIANGLE}, mesh{_mesh}, transfo{Mat4::identity()} {}
Entity::Entity(Mesh *_mesh, Mat4 _transfo) : draw_mode{TRIANGLE}, mesh{_mesh}, transfo{_transfo} {}
Entity::~Entity() {}

void Entity::scale(const Vec3& s)
{
    transfo = transfo * Mat4::CreateScaleMatrix(s);
}

void Entity::translate(const Vec3& t)
{
    transfo = transfo * Mat4::CreateTranslationMatrix(t);
}

/*
 * Angles in radian
 */
void Entity::rotate(const Vec3& r)
{
    if (r.z != 0.f)
        transfo = transfo * Mat4::CreateZRotationMatrix(r.z);
        
    if (r.x != 0.f)
        transfo = transfo * Mat4::CreateXRotationMatrix(r.x);

    if (r.y != 0.f)
        transfo = transfo * Mat4::CreateYRotationMatrix(r.y);

}

void Entity::resetTransformation()
{
    // transfo = Mat4::identity();
    memset(&transfo,0,16*sizeof(float));
    transfo.a[0]=1.f;
    transfo.a[5]=1.f;
    transfo.a[10]=1.f;
    transfo.a[15]=1.f;
}

void Entity::setDrawMode(const DRAW_MODE d_m)
{
    draw_mode = d_m;
}

DRAW_MODE Entity::getDrawMode() const
{
    return draw_mode;
}
