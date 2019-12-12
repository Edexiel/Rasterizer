#ifndef __COLOR_HPP__
#define __COLOR_HPP__

struct Color
{  
    union
    {
        struct 
        {
            unsigned char r, g, b;     
        };
        unsigned char e[3];
    };
    
};

inline Color operator*(Color c, float w)
{
    c.r = (unsigned char)(c.r * w);
    c.g = (unsigned char)(c.g * w);
    c.b = (unsigned char)(c.b * w);

    return c;
}

inline Color operator+(Color c1, Color c2)
{
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    return c1;
}

#endif // __COLOR_HPP__
