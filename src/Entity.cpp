#include "Entity.hpp"

Entity::Entity(): transfo{Mat4::identity()}{}
Entity::Entity(Mesh* _mesh) : mesh{_mesh},transfo{Mat4::identity()}{}
Entity::Entity(Mesh* _mesh, Mat4 _transfo) : mesh{_mesh},transfo{_transfo}{}

Entity::~Entity(){}
