#pragma once

class Vec2
{
public:
    union {
        struct
        {
            float x;
            float y;
        };

        float e[2];
    };

    Vec2();
    Vec2(float, float);
    ~Vec2();

    float getMagnitude() const;
    void Normalize();
    Vec2 operator+(Vec2 &other);
    Vec2 operator*(float float_other);
};

<<<<<<< HEAD

=======
// float cross_product(Vec2& v1, Vec2& v2)
// {
    
// }
>>>>>>> e6cf72ad0cb08e63e750161ecd33454311e0d234
