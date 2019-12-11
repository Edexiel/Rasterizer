#include "light.hpp"
#include "Vec3.hpp"
#include "Color.hpp"
#include "tools.hpp"

Light::Light(Vec3 light, Vec3 camera, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess)
    : m_ambientIntensity{ambientIntensity},
      m_diffuseIntensity{diffuseIntensity},
      m_specularIntensity{specularIntensity},
      m_shininess{shininess},
      camera_pos{camera},
      light_pos{light} {}


<<<<<<< HEAD
=======
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
>>>>>>> 5d5d64de5cb364cf01135f08b8f6c441a603f3a5
