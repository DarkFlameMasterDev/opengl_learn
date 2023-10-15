//
// Created by 曹璐韬 on 2023/8/12.
//
#include "1_two_triangle.h"

#include <iostream>


int two_triangle::create_two_triangle() {
    init_glfw();

    GLFWwindow *window = create_glfw_window();

    if (window == nullptr) {
        return -1;
    }

    // Set the context of our window to the main context of the current thread
    glfwMakeContextCurrent(window);

    // glfwGetProcAddress is the function GLFW get Open GL pointer
    // check if GLAD can use the glfw function in order to initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 注册 framebuffer_size_callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // ********************* 编译着色器 ****************************

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main(){\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main(){\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";
    // vertex shader
    // create a shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // check if the vertexShader compiled successfully
    check_shader(vertexShader, "GL_VERTEX_SHADER");

    // fragment shader
    // create a shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // check if the fragmentShader compiled successfully
    check_shader(fragmentShader, "GL_FRAGMENT_SHADER");

    // ********************* 链接着色器，编译 program ****************************
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check if the program compiled successfully
    check_program(shaderProgram);

    // delete shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
            0.25f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0, -0.5f, 0.0f,
            -0.25f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 2,  // first Triangle
            2, 3, 4   // second Triangle
    };

    unsigned int VAO_handle, VBO_handle, EBO_handle;
    glGenVertexArrays(1, &VAO_handle);
    glGenBuffers(1, &VBO_handle);
    glGenBuffers(1, &EBO_handle);

    // ********************************************************************************
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // 1.绑定 VAO_handle
    glBindVertexArray(VAO_handle);
    // 2.绑定 VBO_handle
    glBindBuffer(GL_ARRAY_BUFFER, VBO_handle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3.绑定 EBO_handle
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4.设置 Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO_handle as the vertex attribute's bound vertex buffer object so afterward we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO_handle afterward so other VAO_handle calls won't accidentally modify this VAO_handle, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray , so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    // ********************************************************************************

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        draw_frame(shaderProgram, VAO_handle);

        // 交换 Buffer
        glfwSwapBuffers(window);

        // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
        glfwPollEvents();
    }

    // 释放/删除之前的分配的所有资源
    glfwTerminate();
    return 0;
}


/**
 * initialize glfw
 */
void two_triangle::init_glfw() {
    // glfw initialize
    glfwInit();

    // Use OpenGL 3.3 version

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // GLFW use core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MacOS specific code
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

/**
 * create_glfw_window and check
 */
GLFWwindow *two_triangle::create_glfw_window() {
    // Create a windows
    GLFWwindow *window = glfwCreateWindow(800, 800, "lucas_opengl", nullptr, nullptr);

    // Check if the window is created successfully
    if (window == nullptr) {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    return window;
}

/**
 * 回调函数，在窗口大小调整的时候，调整 ViewPort 的大小
 * @param window
 * @param width
 * @param height
 */
void two_triangle::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

/**
 * 检测是否有按键输入
 * 如果按下了 esc 就设置当前窗口应该退出
 * @param window
 */
void two_triangle::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void two_triangle::check_shader(unsigned int shader, const string &type) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER:: " << type << " ::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void two_triangle::check_program(unsigned int shaderProgram) {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cout << "ERROR::shaderProgram::COMPILATION_FAILED\n" << infoLog << endl;
    }
}


void two_triangle::draw_frame(unsigned int shaderProgram, unsigned int VAO_handle) {

    // 设置调用 clear 所使用的颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // 清空屏幕
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(shaderProgram);

    // seeing as we only have a single VAO_handle there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO_handle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}