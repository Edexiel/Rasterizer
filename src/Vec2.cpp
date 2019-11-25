#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2() {}

Vec2::Vec2(float _x, float _y) : x{_x}, y{_y} {}

Vec2::~Vec2() {}

// AVX optimization Here
float Vec2::getMagnitude() const
{
    return sqrt(x * x * y * y);
}

void Vec2::Normalize()
{
    float mag = getMagnitude();

    if (mag == 0)
        return;

    x /= mag;
    y /= mag;
}

Vec2 Vec2::operator+(Vec2 &other)
{
    return {x + other.x, y + other.y};
}

Vec2 Vec2::operator*(float other)
{
    return {x * other, y * other};
}
