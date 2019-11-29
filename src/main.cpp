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
#include "math.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    uint screenWidth = 800;
    uint screenHeight = 600;

    float aspect = screenWidth / (float)screenHeight;

    float modres = 1;

    uint resWidth = (uint)(screenWidth / modres);
    uint resHeight = (uint)(screenHeight / modres);

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

    // Time && fps
    double time = 0.f;
    double deltaTime;
    float sample = 1.f; // moyenne sur seconde
    uint frames = 0;
    double time_acc = 0.f;

    Rasterizer renderer{resWidth, resHeight};

    renderer.viewport = Mat4::viewportMatrix(1, -1, resWidth, resHeight);
    renderer.projection = Mat4::orthoMatrix(-aspect, aspect, -1.f, 1.f, 0.f, 100.f);
    // renderer.projection = Mat4::identity();

    Scene scene{};

    //scene.m_light.viewport = &renderer.viewport;
    // scene.entities.push_back(Entity{Mesh::CreateCube(), Mat4{Vec4{1, 0, 0, 0}, Vec4{0, 1, 0, 0}, Vec4{0, 0, 1, 0}, Vec4{0, 0, 0, 1}}});
    scene.entities.push_back(Entity{Mesh::CreateCube()});
    scene.entities[0].scale(1.f, 1.f, 1.f);
    scene.entities[0].translate(0.5f, 0.f, 0.f);
    // scene.entities[0].setDrawMode(TRIANGLE);

    scene.entities.push_back(Entity{Mesh::CreateTriangle()});
    // scene.entities.push_back(Entity{Mesh::CreateSphere(18,32)});
    scene.entities[0].scale(1.f, 1.f, 1.f);
    // scene.entities[1].scale(0.3f, 0.3f, 0.3f);
    scene.entities[1].translate(0.f, 0.f, 0.f);
    // scene.entiti1s[0].rotate(0.10f, 0, 0);1
    scene.entities[1].setDrawMode(TRIANGLE);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        // glfwGetCursorPos(window, &x, &y);
        { // DeltaTime
            deltaTime = glfwGetTime() - time;
            time = glfwGetTime();

            time_acc += deltaTime;
            frames++;

            if (time_acc >= sample)
            {
                std::cout << "FPS: " << 1 / (time_acc / frames) << std::endl;
                frames = 0;
                time_acc = 0.f;
            }
        }
        scene.entities[0].rotate(0, 0.01f, 0);

        // scene.entities[0].rotate(0,0.05f,0);
        // scene.entities[1].rotate(0f,0,0);

        renderer.clear_color_buffer();
        renderer.clear_depth_buffer();

        renderer.render_scene(&scene);
        renderer.draw_scene();

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}