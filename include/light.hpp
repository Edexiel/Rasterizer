#pragma once
#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"

class Light
{

public:
    Light();
    Light(Vec3 v_light, Vec3 V,float ambientLight,float diffuseLight,float specularLight,float alpha);
    ~Light();

    Vec3 v_light;
    Vec3 V; // V is the direction of the camera
    float ambientLight;
    float diffuseLight;
    float specularLight;
    float alpha;

    float diffuse_light(const Vec3&pos, const Vec3& normal);
    float specular_light(const Vec3&pos, const Vec3& normal);
    float apply_light(const Vec3&pos, const Vec3& normal);
};