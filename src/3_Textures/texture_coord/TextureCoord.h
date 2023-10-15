//
// Created by 曹璐韬 on 2023/9/18.
//

#ifndef OPENGL_ENVIRONMENT_TEST_TEXTURECOORD_H
#define OPENGL_ENVIRONMENT_TEST_TEXTURECOORD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "filesystem.h"


class TextureCoord {

public:

    static int create_a_textures();

private:

    static void processInput(GLFWwindow *window);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void init_glfw();

    static GLFWwindow *create_glfw_window();

    static void check_shader(unsigned int shader, const std::string &type);

    static void check_program(unsigned int shaderProgram);
};


#endif //OPENGL_ENVIRONMENT_TEST_TEXTURECOORD_H
