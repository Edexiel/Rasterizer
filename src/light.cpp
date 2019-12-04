#include "light.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include <iostream>
#include <cmath>


Light::Light(){}
Light::Light(Vec3 _v_light,float _ambientLight,float _diffuseLight,float _specularLight,float _alpha): v_light{_v_light},ambientLight{_ambientLight},diffuseLight{_diffuseLight},specularLight{_specularLight},alpha{_alpha} {}

Light::~Light(){}

float Light::diffuse_light(Vertex& v)
{
    v_light.normalize();
    Vec3 pos  = v.position.get_normalize();
    Vec3 to_light = (v_light - pos).get_normalize();
    float diffuse = Vec3::dot_product(to_light, v.normal);

    if (diffuse < 0)
        return 0;
    
    return (diffuseLight * diffuse);
}

float Light::specular_light(Vertex& v)
{
    v_light.normalize();
    Vec3 pos  = v.position.get_normalize();
    Vec3 to_light = (v_light - pos).get_normalize();
    float dotProductLN = (dot_product(to_light, v.normal) * 2);
    if (dotProductLN < 0)
        dotProductLN = 0;

    Vec3 R =  (v.normal * dotProductLN - to_light).get_normalize();
    float spec = specularLight * powf(dot_product(R, V), alpha);
    if (spec < 0)
        return 0;

    return spec;
}

Color Light::apply_light(Vertex& v)
{
    float m_ambientLight = ambientLight;
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

    return v.color * (m_ambientLight + m_diffuseLight + m_specularLight);
}