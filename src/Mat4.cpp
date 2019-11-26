#include "Mat4.hpp"
#include <cmath>

Mat4::Mat4() : a{0} {}
Mat4::Mat4(float f) : a{f} {}
Mat4::Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4)
{
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;
    v[3] = v4;
}
Mat4::Mat4(const float (&array)[16]) : a{*array} {}
Mat4::~Mat4() {}

Mat4 Mat4::identity()
{
    return Mat4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

Mat4 Mat4::viewportMatrix(int x, int y, int width, int height)
{
    return {{width / (x * 2), 0, 0, 0}, {0, height / (y * 2), 0, 0}, {0, 0, 0, 0}, {width * 0.5, height * 0.5, 0, 1}};
}

Mat4 Mat4::orthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
    return {{2 / (right - left), 0, 0, 0}, {0, 2 / (top - bottom), 0, 0}, {0, 0, -2 / (far - near), 0}, {-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1}};
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3 &t)
{
    return Mat4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {t.x, t.y, t.z, 1}};
}

Mat4 Mat4::CreateScaleMatrix(const Vec3 &scale)
{
    return Mat4{{scale.x, 0, 0, 0}, {0, scale.y, 0, 0}, {0, 0, scale.z, 0}, {0, 0, 0, 1}};
}

//AVX
/*
 *  float angle in rad
 */
Mat4 Mat4::CreateXRotationMatrix(const float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    return Mat4{{1, 0, 0, 0}, {0, c, s, 0}, {0, -s, c, 0}, {0, 0, 0, 1}};
}

//AVX
/*
 *  float angle in rad
 */
Mat4 Mat4::CreateYRotationMatrix(const float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    return Mat4{{c, 0, -s, 0}, {0, 1, 0, 0}, {s, 0, c, 0}, {0, 0, 0, 1}};
}

//AVX
/*
 *  float angle in rad
 */
Mat4 Mat4::CreateZRotationMatrix(const float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    return Mat4{{c, s, 0, 0}, {-s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

//AVX
Mat4 Mat4::CreateTransformMatrix(const Vec3 &t, const Vec3 &r, const Vec3 &s)
{
    return CreateTranslationMatrix(t) * (CreateXRotationMatrix(r.x) * CreateYRotationMatrix(r.y) * CreateZRotationMatrix(r.z)) * CreateScaleMatrix(s);
}

Mat4 Mat4::operator+(const Mat4 &other) const
{
    Mat4 res{0};
    for (int i = 0; i < 16; i++)
        res.a[i] = a[i] + other.a[i];

    return res;
}

Mat4 Mat4::operator*(const Mat4 &other) const
{
    Mat4 res = {0};

    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r)
            for (int i = 0; i < 4; ++i)
                res.v[c].e[r] += v[i].e[r] * other.v[c].e[i];
    return res;
}

Vec4 Mat4::operator*(const Vec4 &_v) const
{
    Vec4 res{0, 0, 0, 0};
    //for (int i = 0; i < 4; i++)
    //    for (int j = 0; j < 4; j++)
    //        res.e[i] += v[i].e[j] * _v.e[j];

    res.x = _v.x * v[0].e[0] + _v.y * v[1].e[0] + _v.z * v[2].e[0] + _v.w * v[3].e[0];
    res.y = _v.x * v[0].e[1] + _v.y * v[1].e[1] + _v.z * v[2].e[1] + _v.w * v[3].e[1];
    res.z = _v.x * v[0].e[2] + _v.y * v[1].e[2] + _v.z * v[2].e[2] + _v.w * v[3].e[2];
    res.w = _v.x * v[0].e[3] + _v.y * v[1].e[3] + _v.z * v[2].e[3] + _v.w * v[3].e[3];

    return res;
}
