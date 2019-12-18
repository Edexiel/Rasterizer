#include "Scene.hpp"
#include "Mesh.hpp"
#include "Vec3.hpp"

Scene::Scene(InputManager *im) : _im{im}
{
    // LIGHT
    _camera = Camera{im, (Vec3){0.f, 0.f, 0.f}, 0.f, 0.f, 0.5f, 1.f};
    _light = Light{Vec3{1.0f, 1.f, 1.f}, &_camera, Colorf{1.f, 1.f, 1.f}, 0.2f, 0.4f, 0.4f, 20.f};

    // SCENE ENTITIES
    // Entity sphere{Mesh::CreateSphere(8, 16)};
    // Entity cube{Mesh::CreateCube("media/cratetex.png")};
    // // entities.push_back(Entity{Mesh::CreateCube(nullptr)});
    // cube.setPosition({0.f,0.f,-2.f});

    // entities.push_back(cube);

    Entity sphere{Mesh::CreateSphere(8, 16)};
    sphere.setPosition({2.f, 0.f, -1.f});
    sphere.setScale({0.25f, 0.25f, 0.25f});
    sphere.setDrawMode(LINE);


    Entity teapot{Mesh::LoadObj("media/teapot.obj")};
    teapot.setPosition({0.f,-2.f,-1.f});
    teapot.setScale({0.1f,0.1f,0.1f});

    Entity cubeTexture{Mesh::CreateCube("media/cratetex.png")};
    cubeTexture.setPosition({-1.f,0.f,-1.f});
    cubeTexture.setScale({0.5f,0.5f,0.5f});

    entities.push_back(teapot);
    entities.push_back(cubeTexture);
    entities.push_back(sphere);
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
