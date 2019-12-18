#pragma once
#include <cmath>
#include "Vec4.hpp"

// Column major library
class Mat4
{
public:
    union {
        Vec4 v[4];
        float a[16];
        float aa[4][4];
    };

    Mat4() = default;
    Mat4(float f);
    Mat4(const float (&array)[16]);
    Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4);

    static Mat4 identity();
    static Mat4 viewportMatrix(int x, int y, int width, int height);
    static Mat4 orthoMatrix(float left, float right, float bottom, float top, float near, float far);
    static Mat4 frustum(float left, float right, float bottom, float top, float znear, float zfar);
    static Mat4 perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar);
    static Mat4 CreateTranslationMatrix(const Vec3 &translation);
    static Mat4 CreateScaleMatrix(const Vec3 &scale);
    static Mat4 CreateXRotationMatrix(const float angle);
    static Mat4 CreateYRotationMatrix(const float angle);
    static Mat4 CreateZRotationMatrix(const float angle);
    static Mat4 CreateTransformMatrix(const Vec3 &position, const Vec3 &rotation, const Vec3 &scale);
    Mat4 operator+(const Mat4 &other) const;
    Mat4 operator*(const Mat4 &other) const;
    Vec4 operator*(const Vec4 &v) const;
};

inline Mat4::Mat4(float f) : a{f} {}
inline Mat4::Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4)
{
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;
    v[3] = v4;
}
inline Mat4::Mat4(const float (&array)[16]) : a{*array} {}

inline Mat4 Mat4::identity()
{
    return Mat4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

/**
 * @brief 
 * 
 * @param x largeur du clip space
 * @param y hauteur du clip space
 * @param width  largeur de la viewport
 * @param height hauteur de la viewport
 * 
 * @return Mat4 
 */
inline Mat4 Mat4::viewportMatrix(int x, int y, int width, int height)
{
    return {{(float)width / ((float)x * 2.f), 0.f, 0.f, 0.f}, {0.f, -((float)height / ((float)y * 2.f)), 0.f, 0.f}, {0.f, 0.f, 1.f, 0.f}, {(float)width * 0.5f, (float)height * 0.5f, 0.f, 1.f}};
}

/**
 * @brief Creates orthographic matric (2D)
 * 
 * @param left 
 * @param right 
 * @param bottom 
 * @param top 
 * @param near 
 * @param far 
 * 
 * @return Mat4 
 */
inline Mat4 Mat4::orthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
    return {{2.f / (right - left), 0.f, 0.f, 0.f}, {0.f, 2.f / (top - bottom), 0.f, 0.f}, {0.f, 0.f, -2.f / (far - near), 0.f}, {-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1.f}};
}

/**
 * @brief Creates perspective matric (3D)
 * 
 * @param fovyInDegrees 
 * @param aspectRatio 
 * @param znear 
 * @param zfar 
 * @return Mat4 
 */
inline Mat4 Mat4::perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar)
{
    float ymax, xmax;
    ymax = znear * tanf(fovyInDegrees * (float)M_PI / 360.0f);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}

/**
 * @brief Creates a frustum
 * 
 * @param left 
 * @param right 
 * @param bottom 
 * @param top 
 * @param znear 
 * @param zfar 
 * @return Mat4 
 */
inline Mat4 Mat4::frustum(float left, float right, float bottom, float top, float znear, float zfar)
{
    float nn, rl, tb, fn;
    nn = 2.0f * znear;
    rl = right - left;
    tb = top - bottom;
    fn = zfar - znear;

    return {{nn / rl, 0.f, 0.f, 0.f}, {0.f, nn / tb, 0.f, 0.f}, {(right + left) / rl, (top + bottom) / tb, -(zfar + znear) / fn, -1.0}, {0, 0, -(nn * zfar) / fn, 0.f}};
}

inline Mat4 Mat4::CreateTranslationMatrix(const Vec3 &t)
{
    return Mat4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {t.x, t.y, t.z, 1}};
}

inline Mat4 Mat4::CreateScaleMatrix(const Vec3 &scale)
{
    return Mat4{{scale.x, 0, 0, 0}, {0, scale.y, 0, 0}, {0, 0, scale.z, 0}, {0, 0, 0, 1}};
}

/**
 * @brief Creates a rotation matrix on X axis
 * 
 * @param angle in radians
 * 
 * @return Mat4 
 */
inline Mat4 Mat4::CreateXRotationMatrix(const float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    return Mat4{{1, 0, 0, 0}, {0, c, s, 0}, {0, -s, c, 0}, {0, 0, 0, 1}};
}

/**
 * @brief Creates a rotation matrix on Y axis
 * 
 * @param angle in radians
 * 
 * @return Mat4 
 */
inline Mat4 Mat4::CreateYRotationMatrix(const float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    return Mat4{{c, 0, -s, 0}, {0, 1, 0, 0}, {s, 0, c, 0}, {0, 0, 0, 1}};
}

/**
 * @brief Creates a rotation matrix on Z axis
 * 
 * @param angle in radians
 * 
 * @return Mat4 
 */
inline Mat4 Mat4::CreateZRotationMatrix(const float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    return Mat4{{c, s, 0, 0}, {-s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

inline Mat4 Mat4::CreateTransformMatrix(const Vec3 &t, const Vec3 &r, const Vec3 &s)
{
    return CreateTranslationMatrix(t) * (CreateXRotationMatrix(r.x) * CreateYRotationMatrix(r.y) * CreateZRotationMatrix(r.z)) * CreateScaleMatrix(s);
}

inline Mat4 Mat4::operator+(const Mat4 &other) const
{
    Mat4 res{0};
    
    for (int i = 0; i < 16; i++)
        res.a[i] = a[i] + other.a[i];

    return res;
}

inline Mat4 Mat4::operator*(const Mat4 &other) const
{
    Mat4 res = {0};

    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r)
            for (int i = 0; i < 4; ++i)
                res.v[c].e[r] += v[i].e[r] * other.v[c].e[i];
    return res;
}

inline Vec4 Mat4::operator*(const Vec4 &_v) const
{
    Vec4 res{0, 0, 0, 0};

    // for (int i = 0; i < 4; i++)
    // {
    //     res.e[i] = 0;
    //     for (int j = 0; j < 4; j++)
    //         res.e[i] += v[j].e[i] * _v.e[j];
    // }

    res.x = _v.x * v[0].e[0] + _v.y * v[1].e[0] + _v.z * v[2].e[0] + _v.w * v[3].e[0];
    res.y = _v.x * v[0].e[1] + _v.y * v[1].e[1] + _v.z * v[2].e[1] + _v.w * v[3].e[1];
    res.z = _v.x * v[0].e[2] + _v.y * v[1].e[2] + _v.z * v[2].e[2] + _v.w * v[3].e[2];
    res.w = _v.x * v[0].e[3] + _v.y * v[1].e[3] + _v.z * v[2].e[3] + _v.w * v[3].e[3];

    return res;
}
