#pragma once
#include "Vec3.hpp"
#include "Vertex.hpp"
#include "Mat4.hpp"

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

    Light();
    Light(Vec3 light_pos, Vec3 camera_pos, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess);
    ~Light();

    float diffuse_light(const Vec3 &normal, const Vec3 &light_direction) const;
    float specular_light(const Vec3 &normal, const Vec3 &light_direction, const Vec3 &camera_direction) const;
    float apply_light(Vertex &vertex, Vec3 &camera_pos, Vec3 &light_pos) const;
};