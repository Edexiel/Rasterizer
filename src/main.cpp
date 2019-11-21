#include <iostream>
#include <cstdio>
#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include <vector>

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
            std::cout << m2.aa[i][j] << ", ";
        std::cout << "}" << std::endl;
    }
    std::cout << "vector: "<< std::endl;
    for (int i = 0; i < 4; i++)
        std::cout << vec.e[i] << std::endl;

    std::cout << "matrix * vector: " << std::endl;
    for (int i = 0; i < 4; i++)
        std::cout << vecRes.e[i] << std::endl;
    

}

void test_triangle()
{
    int width = 20;
    int height = 10;

    Vec4 v1{0,0,0,0};
    Vec4 v2{10,0,0,0};
    Vec4 v3{5,20,0,0};
    std::vector<Vec4> vecList;
    
    for (float y = 0; y < height; y++)
    {
        for(float x = 0; x < width; x++)
        {
            float w1 = ( ( (v2.y - v3.y) * (x - v3.x) ) + ( (v3.x - v2.x) * (y - v3.y) ) ) /
                       ( ( (v2.y -v3.y) * (v1.x - v3.x) ) + ( (v3.x - v2.x) * (v1.y - v3.y) ) );

            float w2 = ( ( (v3.y - v1.y) * (x - v3.x) ) + ( (v1.x - v3.x) * (y - v3.y) ) ) /
                       ( ( (v2.y -v3.y) * (v1.x - v3.x) ) + ( (v3.x - v2.x) * (v1.y - v3.y) ) );

            float w3 = 1.f - w1 - w2;
            if (w1 + w2 + w3 == 1)
            {
                std::cout << "1";
                float Px = w1 * v1.x + w2 * v2.x + w3 * v3.x;
                float Py = w1 * v1.y + w2 * v2.y + w3 * v3.y;
                vecList.push_back(Vec4 {Px, Py, 0, 0});
            }
            else
                std::cout << "0";
        }
        std::cout << std::endl;
    }  
}

int main()
{
    test_triangle();
    return 0;
}