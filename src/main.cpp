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
#include "tools.hpp"
#include <cmath>
#include "Camera.hpp"
#include "InputManager.hpp"

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

    float modres = 1.f;

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
    glfwSetKeyCallback(window, key_callback);

    // Time && fps
    double time = 0.f;
    double deltaTime;
    float sample = 1.f; // moyenne sur seconde
    uint frames = 0;
    double time_acc = 0.f;

    Rasterizer renderer{resWidth, resHeight};
    Scene scene{};
    InputManager im{window};
    Camera camera{&im, 0.005f};

    renderer.viewport = Mat4::viewportMatrix(1, -1, resWidth, resHeight);
#if 1 // Perspective or 2D
    renderer.projection = Mat4::perspective(60.f, aspect, 0.01f, 10.f);
#elif
    renderer.projection = Mat4::orthoMatrix(-aspect, aspect, -1.f, 1.f, 0.f, 100.f);
#endif

    // scene.entities.push_back(Entity{Mesh::CreateSphere(25, 25)});
    scene.entities.push_back(Entity{Mesh::CreateCube()});
    scene.entities[0].setDrawMode(TRIANGLE);

    scene.light = (Light){{1.0f, 1.f, 1.f}, {0.0f, 0.0f, 0.f}, 0.2f, 0.4f, 0.4f, 20.f};

    // scene.entities.push_back(Entity{Mesh::CreateVectorLight(scene.light.v_light.x, scene.light.v_light.y, scene.light.v_light.z)});

    //temporary stuff
    Vec3 pos{0.f, 0.f, -1.f};
    Vec3 rot{0.f, 0.f, 0.f};

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
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

        im.update();

        renderer.view = camera.getCameraMatrix();

        renderer.clear_color_buffer();
        renderer.clear_depth_buffer();
        scene.entities[0].translate(pos);
        scene.entities[0].rotate(rot);
        scene.entities[0].scale({0.4f, 0.4f, 0.4f});

        renderer.render_scene(&scene);

        renderer.draw_scene();

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}
