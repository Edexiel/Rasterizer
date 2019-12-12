#pragma once

template<typename T>
class Vec2
{
public:
    union {
        struct
        {
            T x;
            T y;
        };

        T e[2];
    };

    Vec2()=default;
    Vec2(T, T);

    T getMagnitude() const;
    void normalize();
    Vec2<T> operator+(Vec2<T> &other);
    Vec2<T> operator*(T &other);
};

#define Vec2f Vec2<float> 
#define Vec2d Vec2<double> 

template<typename T>
inline Vec2<T>::Vec2(T _x, T _y) : x{_x}, y{_y} {}

template<typename T>
inline T Vec2<T>::getMagnitude() const
{
    return sqrtf(x * x * y * y);
}

template<typename T>
inline void Vec2<T>::normalize()
{
    float mag = getMagnitude();

    if (mag == 0)
        return;

    x /= mag;
    y /= mag;
}
template<typename T>
Vec2<T> Vec2<T>::operator+(Vec2<T> &other)
{
    return {x + other.x, y + other.y};
}

template<typename T>
Vec2<T> Vec2<T>::operator*(T& other)
{
    return {x * other, y * other};
}

