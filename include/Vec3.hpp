#pragma once

class Vec3
{
public:
    union {
        struct
        {
            float x;
            float y;
            float z;
        };

        struct
        {
            float r;
            float g;
            float b;
        };
        float e[3];
    };

    Vec3();
    Vec3(float, float, float);
    ~Vec3();

    float getMagnitude() const;
    void normalize();
    Vec3 get_normalize() const;

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(float float_other) const;

    static float cross_product_z(const Vec3 &v1,const Vec3 &v2) ;
    static Vec3 cross_product(const Vec3 &v1,const Vec3 &v2) ;
    static float dot_product(const Vec3 &v1,const Vec3 &v2) ;
};