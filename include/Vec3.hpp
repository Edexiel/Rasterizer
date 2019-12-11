#pragma once

#include <cmath>
#include <iostream>

class Vec3
{
public:
    union {
        struct
        {
            float x;
            float y;
            float z;
        };

        struct
        {
            float r;
            float g;
            float b;
        };
        float e[3];
    };

    Vec3(float, float, float);
    Vec3() = default;

    static Vec3 normalize(const Vec3 &v);

    void normalize();
    float getMagnitude() const;

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(float float_other) const;

    static float cross_product_z(const Vec3 &v1, const Vec3 &v2);
    static Vec3 cross_product(const Vec3 &v1, const Vec3 &v2);
    static float dot_product(const Vec3 &v1, const Vec3 &v2);
};

inline Vec3::Vec3(float _x, float _y, float _z) : x{_x}, y{_y}, z{_z} {}

inline Vec3 Vec3::normalize(const Vec3 &v)
{
    float mag = v.getMagnitude();
    if (mag == 0)
        return v;

    return {v.x / mag, v.y / mag, v.z / mag};
}

inline void Vec3::normalize()
{

    float mag = getMagnitude();

    if (mag == 0)
        return;

    x /= mag;
    y /= mag;
    z /= mag;
}

inline float Vec3::getMagnitude() const
{    
    return sqrtf(x * x + y * y + z * z);
}

inline Vec3 Vec3::operator+(const Vec3 &other) const
{
    return {x + other.x, y + other.y, z + other.z};
}

inline Vec3 Vec3::operator-(const Vec3 &other) const
{
    return {x - other.x, y - other.y, z - other.z};
}

inline Vec3 Vec3::operator*(float other) const
{
    return {x * other, y * other, z * other};
}

inline float Vec3::cross_product_z(const Vec3 &v1, const Vec3 &v2)
{
    return v1.x * v2.y - v2.x * v1.y;
}

inline Vec3 Vec3::cross_product(const Vec3 &v1, const Vec3 &v2)
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
}

inline float Vec3::dot_product(const Vec3 &v1, const Vec3 &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}