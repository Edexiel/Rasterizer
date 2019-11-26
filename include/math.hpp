#pragma once 

typedef unsigned int uint;

#define DEG(rad) rad * M_PI / 180
#define MIN(a,b) a < b ? a : b
#define MAX(a,b) a > b ? a : b

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

enum DRAW_MODE
{
    POINT,
    TRIANGLE,
    TRIANGLE_STRIP,
    FORM
};
