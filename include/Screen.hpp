#pragma once
#include "Texture.hpp"

class Screen
{
private:
    unsigned int m_width;
    unsigned int m_height;
public:
    Texture render_target;
    Screen(unsigned int width, unsigned int height);
    ~Screen();

    unsigned int getHeight();
    unsigned int getWidth();

    void display();
};
