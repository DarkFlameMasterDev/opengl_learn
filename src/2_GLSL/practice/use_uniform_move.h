//
// Created by 曹璐韬 on 2023/9/9.
//

#ifndef OPENGL_ENVIRONMENT_TEST_USE_UNIFORM_MOVE_H
#define OPENGL_ENVIRONMENT_TEST_USE_UNIFORM_MOVE_H

#include <string>

// GLAD is used to manage Open GL function pointers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class use_uniform_move {

public:
    static int create_a_triangle_with_glsl_uniform_move();

private:

    static void init_glfw();

    static GLFWwindow *create_glfw_window();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void check_shader(unsigned int shader, const std::string &type);

    static void check_program(unsigned int shaderProgram);

    static void processInput(GLFWwindow *window);
};

#endif //OPENGL_ENVIRONMENT_TEST_USE_UNIFORM_MOVE_H
