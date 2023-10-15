//
// Created by 曹璐韬 on 2023/8/12.
//

#include "3_two_triangle_with_two_shader.h"
#include <iostream>

using namespace std;


int two_triangle_with_two_shader::create_two_triangle_with_two_shader() {
    init_glfw();

    GLFWwindow *window = create_glfw_window();

    if (window == nullptr) {
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main(){\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    const char *fragmentShaderSource_1 = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "void main(){\n"
                                         "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                         "}\0";


    const char *fragmentShaderSource_2 = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "void main(){\n"
                                         "    FragColor = vec4(0.2f, 0.55f, 1.0f, 1.0f);\n"
                                         "}\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    check_shader(vertexShader, "GL_VERTEX_SHADER");

    unsigned int fragmentShader_orange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_orange, 1, &fragmentShaderSource_1, nullptr);
    glCompileShader(fragmentShader_orange);
    check_shader(fragmentShader_orange, "GL_FRAGMENT_SHADER");

    unsigned int fragmentShader_blue = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_blue, 1, &fragmentShaderSource_2, nullptr);
    glCompileShader(fragmentShader_blue);
    check_shader(fragmentShader_blue, "GL_FRAGMENT_SHADER");

    unsigned int shaderProgram_orange = glCreateProgram();
    glAttachShader(shaderProgram_orange, vertexShader);
    glAttachShader(shaderProgram_orange, fragmentShader_orange);
    glLinkProgram(shaderProgram_orange);
    check_program(shaderProgram_orange);

    unsigned int shaderProgram_blue = glCreateProgram();
    glAttachShader(shaderProgram_blue, vertexShader);
    glAttachShader(shaderProgram_blue, fragmentShader_blue);
    glLinkProgram(shaderProgram_blue);
    check_program(shaderProgram_blue);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader_orange);
    glDeleteShader(fragmentShader_blue);

    float vertices_1[] = {
            0.25f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0, -0.5f, 0.0f,
    };

    float vertices_2[] = {
            0, -0.5f, 0.0f,
            -0.25f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };

    // arrays
    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);


    // bind VAO_1 VBO_1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // bind VAO_2 VBO_2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        draw_frame_background();
        useProgram(shaderProgram_orange);
        draw_frame(VAO[0]);
        useProgram(shaderProgram_blue);
        draw_frame(VAO[1]);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void two_triangle_with_two_shader::init_glfw() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}


GLFWwindow *two_triangle_with_two_shader::create_glfw_window() {
    GLFWwindow *window = glfwCreateWindow(800, 800, "lucas_opengl", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    return window;
}

void two_triangle_with_two_shader::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void two_triangle_with_two_shader::check_shader(unsigned int shader, const string &type) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER:: " << type << " ::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void two_triangle_with_two_shader::check_program(unsigned int shaderProgram) {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cout << "ERROR::shaderProgram::COMPILATION_FAILED\n" << infoLog << endl;
    }
}


void two_triangle_with_two_shader::useProgram(unsigned int program) {
    glUseProgram(program);
}

void two_triangle_with_two_shader::draw_frame_background() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void two_triangle_with_two_shader::draw_frame(unsigned int VAO) {

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void two_triangle_with_two_shader::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

