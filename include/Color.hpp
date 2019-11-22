#pragma once

struct Color
{
    unsigned char r, g, b;
};

Color operator*(Color c, float w)
{
    c.r *= w;
    c.g *= w;
    c.b *= w;

    return c;
}

Color operator+(Color c1, Color c2)
{
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    return c1;
}