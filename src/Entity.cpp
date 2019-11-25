#include "Entity.hpp"

Entity::Entity() : transfo{Mat4::identity()} {}
Entity::Entity(Mesh *_mesh) : mesh{_mesh}, transfo{Mat4::identity()} {}
Entity::Entity(Mesh *_mesh, Mat4 &_transfo) : mesh{_mesh}, transfo{_transfo} {}

Entity::~Entity() {}

void Entity::scale(float x, float y, float z)
{
    transfo = transfo * Mat4::CreateScaleMatrix({x,y,z});
}

void Entity::translate(float x, float y, float z)
{
    transfo = transfo * Mat4::CreateTranslationMatrix({x,y,z});
}

/*
 *  float x : angle in radian
 *  float z : angle in radian
 *  float y : angle in radian
 */
void Entity::rotate(float x, float y, float z)
{
    if(x != 0.f)
        transfo = transfo * Mat4::CreateXRotationMatrix(x);

    if(y != 0.f)
        transfo = transfo * Mat4::CreateYRotationMatrix(y);

    if(z != 0.f)
        transfo = transfo * Mat4::CreateZRotationMatrix(z);

}
