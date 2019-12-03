#pragma once 
#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"
class light
{
public:
    Vec3 v_light;
    float ambientLight;
    float diffuseLight;
    float specularLight;
    float alpha;

    float diffuse_light(Vertex& n);
    float ambient_light(Vertex& n);
    float specular_light(Vertex& n);
    void  apply_light(Vertex& n);
};
