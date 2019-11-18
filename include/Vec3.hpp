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
    };

    Vec3();
    Vec3(float, float, float);
    ~Vec3();

    float getMagnitude() const;
    void Normalize();
    Vec3 operator+(Vec3 &other);
    Vec3 operator*(float float_other);
};