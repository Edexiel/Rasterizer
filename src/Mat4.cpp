#include "Mat4.hpp"
#include <cmath>

Mat4::Mat4() : mat{0} {}
Mat4::Mat4(float f) : mat{f} {}
// Mat4::Mat4(const Vec4 (&array)[4]) : v_mat{*array} {}
Mat4::Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4)
{
    v_mat[0] = v1;
    v_mat[1] = v2;
    v_mat[2] = v3;
    v_mat[3] = v4;
}

Mat4::Mat4(const float (&array)[16]) : mat{*array} {}
Mat4::~Mat4() {}

static Mat4 CreateTranslationMatrix(const Vec3 &translation)
{
}

static Mat4 CreateScaleMatrix(const Vec3 &scale)
{
    return Mat4{{scale.x, 0, 0, 0}, {0, scale.y, 0, 0}, {0, 0, scale.z, 0}, {0, 0, 0, 1}};
}

//AVX
/*
 *  float angle in degres
 */
static Mat4 CreateXRotationMatrix(float angle)
{
    float c = cosf(angle * M_PI / 180);
    float s = sinf(angle * M_PI / 180);

    return Mat4{{1, 0, 0, 0}, {0, c, s, 0}, {0, -s, c, 0}, {0, 0, 0, 1}};
}

//AVX
static Mat4 CreateYRotationMatrix(float angle)
{
    float c = cosf(angle * M_PI / 180);
    float s = sinf(angle * M_PI / 180);

    return Mat4{{c, 0, -s, 0, 1, 0, s, 0, c}};
}

//AVX
static Mat4 CreateZRotationMatrix(float angle)
{
    float c = cosf(angle * M_PI / 180);
    float s = sinf(angle * M_PI / 180);

    return Mat4{{c, s, 0, -s, c, 0, 0, 0, 1}};
}

//AVX
static Mat4 CreateTransformMatrix(const Vec3 &rotation, const Vec3 &position, const Vec3 &scale)
{
}

Mat4 Mat4::operator*(Mat4 &other)
{
    Mat4 res = {0};

    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r)
            for (int i = 0; i < 4; ++i)
                res.v_mat[c].e[r] += v_mat[i].e[r] * other.v_mat[c].e[i];
    return res;
}

Vec4 Mat4::operator*(Vec4 &v)
{
    Vec4 res {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res.e[i] +=  v_mat[i].e[j] * v.e[j];

    return res;
}