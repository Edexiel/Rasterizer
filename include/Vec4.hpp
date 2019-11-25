#pragma once
#include "Vec3.hpp"

class Vec4
{
public:
    union {
        struct
        {
            float x,y,z,w;
        };

        struct
        {
            float r,g,b,a;
        };
        float e[4];
        Vec3 xyz;
    };

    Vec4();
    Vec4(float _x, float _y, float _z, float _w);
    Vec4(const Vec3 &vec3, float _w);
    ~Vec4();

    void Homogenize();
    float getMagnitude() const;
    void Normalize();
    Vec4 operator+(Vec4 &other);
    Vec4 operator*(float f);
};