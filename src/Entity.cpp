#include "Entity.hpp"

void Entity::update(double DeltaTime)
{
    (void)DeltaTime;
}
void Entity::draw()
{
    scale();
    rotate();
    translate();
}