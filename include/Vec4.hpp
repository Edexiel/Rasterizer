#pragma once
#include "Vec3.hpp"

class Vec4
{
public:
    union {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        struct
        {
            float r;
            float g;
            float b;
            float a;
        };
        float e[4];
    };

    Vec4();
    Vec4(float _x, float _y, float _z, float _w);
    Vec4(const Vec3 &vec3, float _w);
    ~Vec4();

    void Homogenize();
    float getMagnitude() const;
    void Normalize();
    Vec4 operator+(Vec4 &other);
    Vec4 operator*(float float_other);
};