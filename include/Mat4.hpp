#pragma once
#include "Vec4.hpp"


// Column major library
class Mat4
{
public:
    union {
        Vec4 v_mat[4];
        float mat[16];
    };

    Mat4();
    Mat4(float f);
    Mat4(Vec4 (&array)[4]);
    Mat4(float (&array)[16]);
    ~Mat4();
    
    static Mat4 CreateTranslationMatrix(const Vec3 &translation);
    static Mat4 CreateScaleMatrix(const Vec3 &scale);
    static Mat4 CreateXRotationMatrix(float angle);
    static Mat4 CreateYRotationMatrix(float angle);
    static Mat4 CreateZRotationMatrix(float angle);

    static Mat4 CreateTransformMatrix(const Vec3 &rotation, const Vec3 &position, const Vec3 &scale);

    Mat4 operator*(Mat4 &other);
    Vec4 Mat4::operator*(Vec4 &v);
};