#pragma once

#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"
#include "tools.hpp"

class Light
{
private:
    Camera *_camera;
    float _ambientIntensity;
    float _diffuseIntensity;
    float _specularIntensity;
    float _shininess;

    Vec3 _light_pos;
    Colorf _light_color;

public:
    Light() = default;
    Light(const Vec3 light_pos, Camera *camera, Colorf light_color, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess);

    Vec3 getPosition() const;
    void setPosition(const Vec3 &position);
    void correct(const Mat4 &view);

    float diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const;
    float specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const;
    void apply_light(const Vec3 &position, const Vec3 &normal, Color &color) const;
};
/**
 * @brief Construct a new Light:: Light object
 * 
 * @param light 
 * @param camera 
 * @param lightColor Pourquoi cette couleur en float et pas les autres ? Me demandez pas
 * @param ambientIntensity 
 * @param diffuseIntensity 
 * @param specularIntensity 
 * @param shininess 
 */
inline Light::Light(const Vec3 light, Camera *camera, const Colorf lightColor, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess)
    : _camera{camera},
      _ambientIntensity{ambientIntensity},
      _diffuseIntensity{diffuseIntensity},
      _specularIntensity{specularIntensity},
      _shininess{shininess},
      _light_pos{light},
      _light_color{lightColor} {}

inline Vec3 Light::getPosition() const
{
    return _light_pos;
}
inline void Light::setPosition(const Vec3 &position)
{
    _light_pos = position;
}

inline void Light::correct(const Mat4 &view)
{
    _light_pos = (view * _light_pos).homogenize().xyz;
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

/**
 * @brief Apply a light to a color given parameters
 * 
 * @param position 
 * @param normal 
 * @param color 
 */
inline void Light::apply_light(const Vec3 &position, const Vec3 &normal, Color &color) const
{
    // Vec3 light_pos{0, 0, 0};
    const Vec3 v_light = Vec3::normalize(_light_pos - position);
    const Vec3 v_camera = Vec3::normalize(_camera->getPosition() - position);
    const Vec3 v_normal = Vec3::normalize(normal);

    const float diffuse = diffuse_light(v_normal, v_light);
    const float specular = specular_light(v_normal, v_light, v_camera);
    color = color * (_ambientIntensity + diffuse + specular);
    color = color * _light_color;
}
