#pragma once

typedef unsigned int uint;

#define DEG(rad) rad *M_PI / 180
#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

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

// #include <immintrin.h>

// void intrin_ZERO_float(float *a, uint size)
// {
//     size_t x = 0;
//     const size_t inc = 32 / sizeof(*(a)); /*size of 256 bit register over size of variable*/
//     for (; x < n - inc; x += inc)
//     {
//         _mm256_storeu_ps((float *)((a) + x), _mm256_setzero_ps());
//         if (4 == sizeof(*(a)))
//         {
//             switch (n - x)
//             {
//             case 3:
//                 (a)[x] = 0;
//                 x++;
//             case 2:
//                 _mm_storeu_ps((float *)((a) + x), _mm_setzero_ps());
//                 break;
//             case 1:
//                 (a)[x] = 0;
//                 break;
//             case 0:
//                 break;
//             };
//         }
//     }