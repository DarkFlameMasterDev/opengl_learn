//
// Created by 曹璐韬 on 2023/8/1.
//

#ifndef OPENGL_ENVIRONMENT_TEST_HELLO_TRIANGLE_H
#define OPENGL_ENVIRONMENT_TEST_HELLO_TRIANGLE_H

#include <string>

// GLAD is used to manage Open GL function pointers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "lucas-opengl"
//using namespace std;

class hello_triangle {

public:
    static int create_a_triangle();

private:
    static void draw_frame(unsigned int shaderProgram, unsigned int VAO);

    static void processInput(GLFWwindow *window);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void init_glfw();

    static GLFWwindow *create_glfw_window();

    static void check_shader(unsigned int shader, const std::string &type);

    static void check_program(unsigned int shaderProgram);
};


#endif //OPENGL_ENVIRONMENT_TEST_HELLO_TRIANGLE_H
