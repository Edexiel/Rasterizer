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
