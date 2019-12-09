#pragma once

#include "Vec3.hpp"
#include "Color.hpp"

struct Vertex
{
    Vec3 position;
    Color color;
    Vec3 normal;
    float u;
    float v;
};
