#pragma once

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

Color operator*(Color c, float w);
Color operator+(Color c1, Color c2);