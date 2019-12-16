#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Color.hpp"

class Vertex
{
private:
public:
    Vec3 position;
    Color color;
    Vec3 normal;

    Vertex() = default;
    Vertex(Vec3 position, Color color);
    Vertex(Vec3 position, Color color, Vec3 normal);
};

inline Vertex::Vertex(Vec3 _position, Color _color):position{_position},color{_color}{}
inline Vertex::Vertex(Vec3 _position, Color _color, Vec3 _normal):position{_position},color{_color},normal{_normal}{}