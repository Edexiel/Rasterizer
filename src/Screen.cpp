#include "Screen.hpp"

Screen::Screen(unsigned int width, unsigned int height) : render_target{width,height}{}

Screen::~Screen(){}

void Screen::display()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, render_target.texture_name);
    render_target.clearBuffer();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(-1, 1);

    glTexCoord2f(1, 0);
    glVertex2f(1, 1);

    glTexCoord2f(1, 1);
    glVertex2f(1, -1);

    glTexCoord2f(0, 1);
    glVertex2f(-1, -1);

    glEnd();
}