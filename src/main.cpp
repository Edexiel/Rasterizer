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
#include "Texture.hpp"
#include "Scene.hpp"
#include "Rasterizer.hpp"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char *argv[])
{
    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;

    float modres = 1;

    unsigned int resWidth = screenWidth / modres;
    unsigned int resHeight = screenHeight / modres;

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
    // glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Rasterizer", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return -1;
    }

    // glfwSwapInterval(1); // Enable v-sync

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
    glfwSetKeyCallback(window, key_callback);

    double time;
    double deltaTime;

    Texture target{resWidth, resHeight, {255, 255, 255}};
    target.clearBuffer();

    GLuint buffer;
    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D, buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Serious stuff

    // Scene scene{};

    // Mesh mesh_triangle{}

    // Entity e_triangle{};
    // e_triangle.mesh =
    // scene.entities.push_back()

    // Main loop
    Vertex v1 {{250, 50, 0}, {255, 0, 0}};
    Vertex v2 {{500, 50, 0}, {0, 255, 0}};
    Vertex v3 {{375, 300, 0}, {0, 0, 255}};
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // DeltaTime
        {
            deltaTime = glfwGetTime() - time;
            time = glfwGetTime();
        }

        std::cout << "FPS: " << 1 / deltaTime << std::endl;
        // Resize viewport
        // glfwGetWindowSize(window, &screenWidth, &screenHeight);

        // glViewport(0, 0, screenWidth, screenHeight);
        // glClearColor(0.5, 0.5, 0.5, 1);

        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // clearBuffer(&buff[0], resWidth, resHeight, rose);

        // Present buffer
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, buffer);
        target.clearBuffer();

        Rasterizer::render_triangle(v1, v2, v3, &target);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resWidth, resHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, target.getPixels());


        glBegin(GL_QUADS);

        glTexCoord2f(0, 1);
        glVertex2f(-1, 1);

        glTexCoord2f(1, 1);
        glVertex2f(1, 1);

        glTexCoord2f(1, 0);
        glVertex2f(1, -1);

        glTexCoord2f(0, 0);
        glVertex2f(-1, -1);

        glEnd();

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}