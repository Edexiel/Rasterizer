#include "Scene.hpp"
#include "Mesh.hpp"
#include "Vec3.hpp"

Scene::Scene(InputManager *im) : _im{im}
{

    // LIGHT
    _camera = Camera{im, (Vec3){0.f, 0.f, 0.f}, 0.f, 0.f, 0.5f, 1.f};
    _light = Light{Vec3{1.0f, 1.f, 1.f}, &_camera, Colorf{1.f, 1.f, 1.f}, 0.2f, 0.4f, 0.4f, 20.f};

    // SCENE ENTITIES

    Entity sphere{Mesh::CreateSphere(8, 16)};
    sphere.setPosition({0.f,0.f,-2.f});

    entities.push_back(sphere);
    // entities.push_back(Entity{Mesh::CreateCube("media/cratetex.png")});
    // entities.push_back(Entity{Mesh::CreateCube(nullptr)});
    // entities[0].scale(0.9f, 0.9f, 0.9f);
    // entities[0].setDrawMode(LINE);
}

Scene::~Scene()
{
    for (Entity &entity : entities)
    {
        delete entity.mesh;
    }
}

void Scene::update(float deltaTime)
{
    _im->update();
    _camera.update(deltaTime);

    for (Entity& entity : entities)
    {
        // entity.update(deltaTime);
        entity.draw();
    }
    
}
