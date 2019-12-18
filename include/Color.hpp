#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "Vec3.hpp"

template <typename T>
struct t_Color
{
    union {
        struct
        {
            T r, g, b;
        };
        T e[3];
    };
};

#define Color t_Color<unsigned char>
#define Colorf t_Color<float>

template <typename T>
inline t_Color<T> operator*(t_Color<T> c, float w)
{
    c.r = (T)(c.r * w);
    c.g = (T)(c.g * w);
    c.b = (T)(c.b * w);

    return c;
}

template <typename T>
inline t_Color<T> operator+(t_Color<T> c1, t_Color<T> c2)
{
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;

    return c1;
}

template <typename T>
inline t_Color<T> operator*(t_Color<T> c1, Vec3 c2)
{
    c1.r = (T)(c1.r * c2.r);
    c1.g = (T)(c1.g * c2.g);
    c1.b = (T)(c1.b * c2.b);

    return c1;
}

inline t_Color<unsigned char> operator*(t_Color<unsigned char> c1, t_Color<float> c2)
{
    c1.r = (unsigned char)(c1.r * c2.r);
    c1.g = (unsigned char)(c1.g * c2.g);
    c1.b = (unsigned char)(c1.b * c2.b);

    return c1;
}

#endif // __COLOR_HPP__
