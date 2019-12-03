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
/*
* x : largeur du clip space
* y: hauteur du clip space
* width : largeur de la viewport
* height : hauteur de la viewport
*/
Mat4 Mat4::viewportMatrix(int x, int y, int width, int height)
{
    return {{(float)width / ((float)x * 2.f), 0.f, 0.f, 0.f}, {0.f, -((float)height / ((float)y * 2.f)), 0.f, 0.f}, {0.f, 0.f, 1.f, 0.f}, {(float)width * 0.5f, (float)height * 0.5f, 0.f, 1.f}};
}

Mat4 Mat4::orthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
    return {{2.f / (right - left), 0.f, 0.f, 0.f}, {0.f, 2.f / (top - bottom), 0.f, 0.f}, {0.f, 0.f, -2.f / (far - near), 0.f}, {-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1.f}};
}

static Mat4 perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar)
{
    float ymax, xmax;
    // float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}

static Mat4 frustum(float left, float right, float bottom, float top, float znear, float zfar)
{
    float nn, rl, tl, fn;
    nn = 2.0 * znear;
    rl = right - left;
    tl = top - bottom;
    fn = zfar - znear;

    return {{nn / rl, 0.f, 0.f, 0.f}, {0.f, nn / tl, 0.f, 0.f}, {(right + left) / rl, (top + bottom) / tl, (-zfar - znear) / fn, -1.0}, {0,0, (-nn * zfar) / fn, 0.f}};
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
