#pragma once
#include "Vec4.hpp"

// Column major library
class Mat4
{
public:
    union {
        Vec4  v[4];
        float a[16];
        float aa[4][4];
    };

    Mat4();
    Mat4(float f);
    Mat4(const float (&array)[16]);
    Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4);
    ~Mat4();

    static Mat4 identity();
    static Mat4 viewportMatrix( int x, int y, int width, int height);
    static Mat4 orthoMatrix( float left, float right, float bottom,float top,float near,float far);
    static Mat4 frustum(float left,float right, float bottom, float top,float znear, float zfar);
    static Mat4 perspective(float fovyInDegrees, float aspectRatio,float znear, float zfar);
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