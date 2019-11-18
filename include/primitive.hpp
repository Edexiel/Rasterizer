#pragma once

#include <vector>
#include "Vector3D.hpp"

class Shape
{
protected:
    std::vector<Vector3f> points;
    short m_draw_mode;
    Vector3f origin;
    Color m_color;
    Vector3f m_scale;

public:
    Shape();
    Shape(Vector3f origin, short draw_mode);
    virtual ~Shape();

    virtual Vector3f &getOrigin();
    virtual void draw() = 0;
    virtual void setDrawMode(short draw_mode);
    virtual void setColor(Color);
    virtual void setScale(Vector3f scale);
    virtual void setOrigin(Vector3f origin);
    // virtual void setTexture();
    // virtual void move(Vector3f &, float divider);
};

class Cube : public Shape
{
private:
public:
    Cube(Vector3f origin);
    Cube(Vector3f origin,Vector3f scale);
    ~Cube();
    virtual void draw() override;
};

class Cone : public Shape
{
private:
public:
    Cone(Vector3f origin, unsigned int l);
    ~Cone();
    virtual void draw() override;
};

class Triedre : public Shape
{
private:
    Cone cone;
public:
    Triedre(Vector3f origin);
    ~Triedre();
    virtual void draw();
};

class Sphere : public Shape
{
private:
    unsigned int m_l;
    unsigned int m_L;

public:
    Sphere(Vector3f origin, unsigned int l, unsigned int L);
    ~Sphere();
    virtual void draw() override;
    Vector3f sp(unsigned int i, unsigned int j, unsigned int l, unsigned int L);
};