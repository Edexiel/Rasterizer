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

    Color diffuse_light(Vertex& n);
    Color ambient_light(Vertex& n);
    void  apply_light(Vertex& n);
};
