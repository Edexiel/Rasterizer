#include <iostream>
#include <cstdio>
#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"


void matrix_test()
{
    Mat4 m({1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
    Mat4 m2(m);
    Vec4 vec {10, 100, 1000, 1};
    Vec4 vecRes = m * vec;

    std::cout << "matrix: "<< std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "{";
        for (int j = 0; j < 4; j++)
            std::cout << m2._mat[i][j] << ", ";
        std::cout << "}" << std::endl;
    }
    std::cout << "vector: "<< std::endl;
    for (int i = 0; i < 4; i++)
        std::cout << vec.e[i] << std::endl;

    std::cout << "matrix * vector: " << std::endl;
    for (int i = 0; i < 4; i++)
        std::cout << vecRes.e[i] << std::endl;
    

}

int main()
{
    matrix_test();
    return 0;
}