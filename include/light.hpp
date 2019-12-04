#pragma once
#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"

class Light
{

public:
    Light();
    Light(Vec3 v_light,float ambientLight,float diffuseLight,float specularLight,float alpha);
    ~Light();

    Vec3 v_light;
    Vec3 V;
    float ambientLight;
    float diffuseLight;
    float specularLight;
    float alpha;

    float diffuse_light(Vertex &n);
    float specular_light(Vertex &n);
    Color apply_light(Vertex &n);
};
