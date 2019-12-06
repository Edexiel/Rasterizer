#pragma once

typedef unsigned int uint;

// #define DEG(rad) rad *M_PI / 180
// #define MIN(a, b) a < b ? a : b
// #define MAX(a, b) a > b ? a : b

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
    LINE,

    FORM
};

template<class T>
T clamp(T v, T lo, T hi )
{
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}


// #define intrin_ZERO_float(a,size)
// {
//     size_t x = 0;
//     for (; x < size - 8; x += 8)
//     {
//         _mm256_storeu_ps((a) + x, _mm256_setzero_ps());
//         switch (size - x)
//         {
//         case 3:
//             (a)[x] = 0;
//             x++;
//         case 2:
//             _mm_storeu_ps((a) + x, _mm_setzero_ps());
//             break;
//         case 1:
//             (a)[x] = 0;
//             break;
//         case 0:
//             break;
//         };
//     }
// }