#include "Entity.hpp"

Entity::Entity(){}
Entity::Entity(Mesh* _mesh, Mat4& _transfo) : mesh{_mesh},transfo{_transfo}{}

Entity::~Entity(){}
