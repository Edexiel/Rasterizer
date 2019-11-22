#include "Scene.hpp"
#include "Mesh.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Entity &e : entities)
    {
        delete e.mesh;
    }
}