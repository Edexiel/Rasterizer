#pragma once
#include "Texture.hpp"

class Screen
{
public:
    Texture render_target;
    Screen(unsigned int width,unsigned int height);
    ~Screen();

    void display();
};

