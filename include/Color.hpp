#pragma once

struct Color
{
    unsigned char r, g, b;
};

Color operator*(Color c, float w);
Color operator+(Color c1, Color c2);