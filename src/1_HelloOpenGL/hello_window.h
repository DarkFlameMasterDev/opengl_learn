//
// Created by 曹璐韬 on 2023/7/31.
//

#ifndef OPENGL_ENVIRONMENT_TEST_HELLO_WINDOW_H
#define OPENGL_ENVIRONMENT_TEST_HELLO_WINDOW_H

// GLAD is used to manage Open GL function pointers
#include <glad/glad.h>

#include <GLFW/glfw3.h>



class hello_window {
public:
    static int create_a_window();

private:
    static void draw_frame();

    static void processInput(GLFWwindow *window);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void init_glfw();

    static GLFWwindow *create_glfw_window();
};


#endif //OPENGL_ENVIRONMENT_TEST_HELLO_WINDOW_H
