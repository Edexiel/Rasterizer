#include "Vec3.hpp"
#include <cmath>

Vec3::Vec3() {}

Vec3::Vec3(float _x, float _y, float _z) : x{_x}, y{_y}, z{_z} {}

Vec3::~Vec3() {}

// AVX optimization Here
float Vec3::getMagnitude() const
{
    return sqrtf(x * x + y * y + z * z);
}

void Vec3::Normalize()
{
    float mag = getMagnitude();

    if (mag == 0)
        return;

    x /= mag;
    y /= mag;
    z /= mag;
}
Vec3 Vec3::get_normalize() const
{
    float mag = getMagnitude();
    if (mag == 0) {return *this;}

    return {x / mag, y / mag, z / mag};
}
Vec3 Vec3::operator+(Vec3 &other)
{
    return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator*(float other)
{
    return {x * other, y * other, z * other};
}

float cross_product(Vec3& v1, Vec3& v2)
{
    return (v1.x) * (v2.y) - (v2.x) * (v1.y);   
}

float dot_product(Vec3& v1, Vec3& v2)
{
    return v1.x + v2.x + v1.y + v2.y + v1.z + v2.z;
}