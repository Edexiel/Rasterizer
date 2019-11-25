#include <iostream>
#include <cstdio>
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
    uint screenWidth = 800;
    uint screenHeight = 600;

    float modres = 1;

    uint resWidth = screenWidth / modres;
    uint resHeight = screenHeight / modres;

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
    glfwSetKeyCallback(window, key_callback);

    double time;
    double deltaTime;

    // Texture target{resWidth, resHeight,{0xFF,0xFF,0xFF}};

    Rasterizer renderer{&resWidth,&resHeight};


    //Serious stuff

    Scene scene{};

    // Mesh mesh_triangle{}

    // Entity e_triangle{};
    // e_triangle.mesh =
    // scene.entities.push_back()

    // Main loop
    Vertex v1 {{-1000, 50, 0}, {255, 0, 0}};
    Vertex v2 {{800, 50, 0}, {0, 255, 0}};
    Vertex v3 {{-350, -300, 0}, {0, 0, 255}};

    float sample = 1.f; // moyenne d'une seconde
    uint frames;
    double time_acc;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        {   // DeltaTime
            deltaTime = glfwGetTime() - time;
            time = glfwGetTime();

            time_acc += deltaTime;
            frames++;

            if(time_acc >= sample)
            {
                std::cout << "FPS: " << 1 / (time_acc/frames) << std::endl;
                frames = 0;
                time_acc = 0.f;
            }
        }

        // Resize viewport
        // glfwGetWindowSize(window, &screenWidth, &screenHeight);

        // glViewport(0, 0, screenWidth, screenHeight);
        // glClearColor(0.5, 0.5, 0.5, 1);

        // Present buffer
        //renderer.draw_triangle(v1, v2, v3);
        renderer.render_scene(&scene);
        

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}