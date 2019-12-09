#include "light.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "tools.hpp"

Light::Light() {}
Light::Light(Vec3 light, Vec3 camera, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess)
    : m_ambientIntensity{ambientIntensity},
      m_diffuseIntensity{diffuseIntensity},
      m_specularIntensity{specularIntensity},
      m_shininess{shininess},
      camera_pos{camera},
      light_pos{light} {}

Light::~Light()
{
}

float Light::diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const
{
    const float diffuseTerm = clamp(Vec3::dot_product(light_direction, normal), 0.f, 1.f);

    return m_diffuseIntensity * diffuseTerm; //mat_reflectance
}

float Light::specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const
{
    float specular_term{0};

    // Vec3 to_light = (m_light - position).get_normalize();

    if (Vec3::dot_product(light_direction, normal) > 0)
    {
        // Vec3 R = (normal * dotProductLN - to_light).get_normalize();
        const Vec3 half_vect = (light_direction + camera_direction).get_normalize();
        specular_term = powf(Vec3::dot_product(normal, half_vect), m_shininess);
    }
    return m_specularIntensity * specular_term; // mat_specular
}

float Light::apply_light(Vertex &vertex, Vec3 &camera_pos, Vec3 &light_pos) const
{
    const Vec3 v_light{(light_pos - vertex.position).get_normalize()};
    const Vec3 v_camera{(camera_pos - vertex.position).get_normalize()};
    const Vec3 v_normal{vertex.normal.get_normalize()};

    const float diffuse = diffuse_light(vertex.position, v_normal);
    const float specular = specular_light(vertex.position, v_normal, v_camera);

    vertex.color = vertex.color * (m_ambientIntensity + diffuse + specular);
}