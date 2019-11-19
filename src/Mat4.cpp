#include "Mat4.hpp"

Mat4::Mat4() : mat{0} {}
Mat4::Mat4(float f) : mat{f} {}

Mat4::Mat4(Vec4 (&array)[4])
{
}

Mat4::Mat4(float (&array)[16])
{
}

Mat4::~Mat4() {}

static Mat4 CreateTranslationMatrix(const Vec3 &translation)
{

}

static Mat4 CreateScaleMatrix(const Vec3 &scale)
{

}

//AVX
static Mat4 CreateXRotationMatrix(float angle)
{
    
}

//AVX
static Mat4 CreateYRotationMatrix(float angle)
{

}

//AVX
static Mat4 CreateZRotationMatrix(float angle)
{

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
}