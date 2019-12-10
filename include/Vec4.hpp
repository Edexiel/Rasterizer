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
        // __m128 i;
        float e[4];
        Vec3 xyz;
    };

    Vec4()=default;
    Vec4(float _x, float _y, float _z, float _w);
    Vec4(const Vec3 &vec3, float _w);

    Vec4 &homogenize();
    void normalize();
    Vec4 operator+(Vec4 &other);
    Vec4 operator*(float f);
};

inline Vec4::Vec4(float _x, float _y, float _z, float _w) : x{_x}, y{_y}, z{_z}, w{_w} {}
inline Vec4::Vec4(const Vec3 &vec3, float _w = 1.0f)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = _w;
}

inline Vec4& Vec4::homogenize()
{
    if (w == 0 || w == 1)
        return *this;

    x /= w;
    y /= w;
    z /= w;

    return *this;
}

inline Vec4 Vec4::operator+(Vec4 &other)
{
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

inline Vec4 Vec4::operator*(float other)
{
    return {x * other, y * other, z * other, w * other};
}