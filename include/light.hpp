#pragma once
#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"
#include "tools.hpp"


class Light
{
private:
    float m_ambientIntensity;
    float m_diffuseIntensity;
    float m_specularIntensity;
    float m_shininess;

public:
    Vec3 camera_pos;
    Vec3 light_pos;

    Light()=default;
    Light(Vec3 light_pos, Vec3 camera_pos, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess);

    float diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const;
    float specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const;
    void apply_light(const Vec3& position,const Vec3& normal, Color& color, Vec3 &camera_pos, Vec3 &light_pos) const;
};

inline void Light::apply_light(const Vec3 &position, const Vec3 &normal, Color &color, Vec3 &camera_pos, Vec3 &light_pos) const
{
    const Vec3 v_light = Vec3::normalize(light_pos - position);
    const Vec3 v_camera = Vec3::normalize(camera_pos - position);
    const Vec3 v_normal = Vec3::normalize(normal);

    const float diffuse = diffuse_light(v_normal, v_light);
    const float specular = specular_light(v_normal, v_light, v_camera);

    color = color * (m_ambientIntensity + diffuse + specular);
}

inline float Light::diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const
{
    const float diffuseTerm = clamp(Vec3::dot_product(light_direction, normal), 0.f, 1.f);

    return m_diffuseIntensity * diffuseTerm; //mat_reflectance
}

inline float Light::specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const
{
    float specular_term{0};

    if (Vec3::dot_product(normal, light_direction) > 0)
    {
        const Vec3 half_vect = Vec3::normalize(light_direction + camera_direction);
        specular_term = powf(Vec3::dot_product(normal, half_vect), m_shininess);
    }
    return m_specularIntensity * specular_term; // mat_specular
}

