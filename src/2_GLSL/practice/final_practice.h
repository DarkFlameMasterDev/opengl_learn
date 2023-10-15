//
// Created by 曹璐韬 on 2023/9/18.
//

#ifndef OPENGL_ENVIRONMENT_TEST_FINAL_PRACTICE_H
#define OPENGL_ENVIRONMENT_TEST_FINAL_PRACTICE_H

#include <string>

// GLAD is used to manage Open GL function pointers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//using namespace std;

class final_practice {

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

#endif //OPENGL_ENVIRONMENT_TEST_FINAL_PRACTICE_H
