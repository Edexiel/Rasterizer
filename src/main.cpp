#include <iostream>
#include <cstdio>
#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <ctime>
#include <string.h>
#include "Color.hpp"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void clearBuffer(Color *buffer, unsigned int screen_width, unsigned int screen_height)
{
    memset(buffer, 127, screen_width * screen_height * sizeof(Color));
}

int main(int argc, char *argv[])
{
    int screenWidth = 800;
    int screenHeight = 600;

    glfwGetTime();

    // Init GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "glfwInit failed.\n");
        return -1;
    }

    // Tell GLFW to create a OpenGL 3.1 context on next glfwCreateWindow() call
    // 3.1 is the smallest version supported on this machine
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Rasterizer", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1); // Enable v-sync

    // We make the OpenGL context current on this calling thread for the window
    // It's mandatory before any OpenGL call
    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGL())
    {
        fprintf(stderr, "gladLoadGL failed.\n");
        glfwTerminate();
        return -1;
    }

    std::srand(std::time(nullptr));

    double time;
    double deltaTime;
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // DeltaTime
        {
            deltaTime = glfwGetTime() - time;
            time = glfwGetTime();
        }

        // Resize viewport
        // glfwGetWindowSize(window, &screenWidth, &screenHeight);

        // glViewport(0, 0, screenWidth, screenHeight);
        // glClearColor(0.5, 0.5, 0.5, 1);

        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Present buffer
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}