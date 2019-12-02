#include "light.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include <iostream>
float light::diffuse_light(Vertex& v)
{
    v_light.Normalize();
    v.normal = v.position.get_normal();
    // Vec3 to_light = (v_light - v.normal).get_normalize();
    // Vec3 LdotN = light
    float diffuse = dot_product(v_light, v.normal);

    if (diffuse > 0)
        return diffuseLight * diffuse;
    else
        return 0;
}

float light::ambient_light(Vertex& v)
{
    return ambientLight;
}

void light::apply_light(Vertex& v)
{
    float m_ambientLight = ambient_light(v);
    float m_diffuseLight = diffuse_light(v);
    
    if( v.color.r * (m_ambientLight + m_diffuseLight)< 255)
        v.color.r = v.color.r * (m_diffuseLight);
    else
        v.color.r = 255;

    if(v.color.g * (m_ambientLight + m_diffuseLight) < 255)
        v.color.g = v.color.g * (m_diffuseLight);
    else
        v.color.g = 255;

    if(v.color.b * (m_ambientLight + m_diffuseLight) < 255)
        v.color.b = v.color.b * (m_diffuseLight);
    else
        v.color.b = 255;

    // v.color = v.color * (m_ambientLight + m_diffuseLight);
}