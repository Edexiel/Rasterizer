#include "Vec4.hpp"
#include <cmath>

Vec4::Vec4() {}

Vec4::Vec4(float _x, float _y, float _z, float _w) : x{_x}, y{_y}, z{_z}, w{_w} {}

Vec4::Vec4(const Vec3 &vec3, float _w = 1.0f)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = _w;
}

Vec4::~Vec4() {}

void Vec4::Homogenize()
{
    if (w == 0 || w == 1)
        return;

    x /= w;
    y /= w;
    z /= w;
}

// AVX optimization Here
float Vec4::getMagnitude() const
{
    return sqrtf(x * x * y * y * z * z);
}

void Vec4::Normalize()
{
    float mag = getMagnitude();

    if (mag == 0)
        return;

    x /= mag;
    y /= mag;
    z /= mag;
}

Vec4 Vec4::operator+(Vec4 &other)
{
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Vec4 Vec4::operator*(float other)
{
    return {x * other, y * other, z * other, w * other};
}
