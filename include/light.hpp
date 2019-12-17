#pragma once

#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"
#include "tools.hpp"

class Light
{
private:
    float _ambientIntensity;
    float _diffuseIntensity;
    float _specularIntensity;
    float _shininess;
    

public:
    Vec3 camera_pos;
    Vec3 light_pos;
    Vec3 light_color;

    Light()=default;
    Light(const Vec3 light_pos,const Vec3 camera_pos, Vec3 light_color, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess);

    float diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const;
    float specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const;
    void apply_light(const Vec3 &position, const Vec3 &normal,Color &color,const Vec3 &_camera_pos,const Vec3 &_light_pos) const;
};

inline Light::Light(const Vec3 light,const Vec3 camera, Vec3 lightColor, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess)
    : _ambientIntensity{ambientIntensity},
      _diffuseIntensity{diffuseIntensity},
      _specularIntensity{specularIntensity},
      _shininess{shininess},
      camera_pos{camera},
      light_pos{light},
      light_color{lightColor} 
      {}

inline void Light::apply_light(const Vec3 &position, const Vec3 &normal,Color &color,const Vec3 &_camera_pos,const Vec3 &_light_pos) const
{
    const Vec3 v_light = Vec3::normalize(_light_pos - position);
    const Vec3 v_camera = Vec3::normalize(_camera_pos - position);
    const Vec3 v_normal = Vec3::normalize(normal);

    const float diffuse = diffuse_light(v_normal, v_light);
    const float specular = specular_light(v_normal, v_light, v_camera);
    color = color * (_ambientIntensity + diffuse + specular);
    color = color * light_color;
}

inline float Light::diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const
{
    const float diffuseTerm = clamp(Vec3::dot_product(light_direction, normal), 0.f, 1.f);

    return _diffuseIntensity * diffuseTerm; //mat_reflectance
}

inline float Light::specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const
{
    float specular_term{0};

    if (Vec3::dot_product(normal, light_direction) > 0)
    {
        const Vec3 half_vect = Vec3::normalize(light_direction + camera_direction);
        specular_term = powf(Vec3::dot_product(normal, half_vect), _shininess);
    }
    return _specularIntensity * specular_term; // mat_specular
}

