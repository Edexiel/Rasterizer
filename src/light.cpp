#include "light.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include <iostream>
#include <cmath>


Light::Light(){}
Light::Light(Vec3 _v_light, Vec3 _V, float _ambientLight,float _diffuseLight,float _specularLight,float _alpha): v_light{_v_light}, V {_V},ambientLight{_ambientLight},diffuseLight{_diffuseLight},specularLight{_specularLight},alpha{_alpha} {}

Light::~Light(){}

float Light::diffuse_light(const Vec3&p, const Vec3& n)
{
    v_light.normalize();
    Vec3 pos  = p.get_normalize();
    Vec3 to_light = (v_light - pos).get_normalize();
    float diffuse = Vec3::dot_product(to_light, n);

    if (diffuse < 0)
        return 0;
    
    return (diffuseLight * diffuse);
}

float Light::specular_light(const Vec3&p, const Vec3& n)
{
    v_light.normalize();
    Vec3 pos  = p.get_normalize();
    Vec3 to_light = (v_light - pos).get_normalize();
    float dotProductLN = (Vec3::dot_product(to_light, n) * 2);
    if (dotProductLN < 0)
         return 0;

    Vec3 R =  (n * dotProductLN - to_light).get_normalize();
    float spec = specularLight * powf(Vec3::dot_product(R, V), alpha);
    if (spec < 0)
        return 0;

    return spec;
}

float Light::apply_light(const Vec3&pos, const Vec3& normal)
{
    float m_ambientLight = ambientLight;
    float m_diffuseLight = diffuse_light(pos, normal);
    float m_specularLight = specular_light(pos, normal);

    return m_ambientLight + m_diffuseLight + m_specularLight;
}