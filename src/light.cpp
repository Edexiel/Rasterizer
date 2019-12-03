#include "light.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include <iostream>
#include <cmath>
float light::diffuse_light(Vertex& v)
{
    v_light.Normalize();
    Vec3 pos  = v.position.get_normal();
    Vec3 to_light = (v_light - pos).get_normal();
    float diffuse = dot_product(to_light, v.normal);

    if (diffuse < 0)
        return 0;
    else
        return (diffuseLight * diffuse);
}

float light::ambient_light(Vertex& v)
{
    return ambientLight;
}

float light::specular_light(Vertex& v)
{
    v_light.Normalize();
    Vec3 pos  = v.position.get_normal();
    Vec3 to_light = (v_light - pos).get_normal();
    Vec3 R =  ((v.normal * dot_product(to_light, v.normal) * 2) - to_light).get_normal();
    Vec3 V {0,0, 1.f};
    float spec = specularLight * pow(dot_product(R, V), alpha);
}

void light::apply_light(Vertex& v)
{
    float m_ambientLight = ambient_light(v);
    float m_diffuseLight = diffuse_light(v);
    float m_specularLight = specular_light(v);
    // if( v.color.r * (m_ambientLight + m_diffuseLight)< 255)
    //     v.color.r = v.color.r * (m_diffuseLight);
    // else
    //     v.color.r = 255;

    // if(v.color.g * (m_ambientLight + m_diffuseLight) < 255)
    //     v.color.g = v.color.g * (m_diffuseLight);
    // else
    //     v.color.g = 255;

    // if(v.color.b * (m_ambientLight + m_diffuseLight) < 255)
    //     v.color.b = v.color.b * (m_diffuseLight);
    // else
    //     v.color.b = 255;

    v.color = v.color * (m_ambientLight + m_diffuseLight + m_specularLight);
}