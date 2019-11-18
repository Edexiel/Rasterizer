#include "Mat4.hpp"

Mat4::Mat4() : mat{0}{}
Mat4::Mat4(float f): mat{f}{}

Mat4::Mat4(Vec4 (&array)[4])
{
}

Mat4::Mat4(float (&array)[16])
{
}

Mat4::~Mat4(){}

Mat4 Mat4::operator*(Mat4 &other)
{
    Mat4 res = {0};

    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r)
            for (int i = 0; i < 4; ++i)
                res.v_mat[c].e[r] += v_mat[i].e[r] * other.v_mat[c].e[i];
    return res;
}

Vec4 Mat4::operator*(float f)
{
}