//
// Created by 曹璐韬 on 2023/9/9.
//

#include "use_uniform_move.h"

#include <iostream>
#include <cmath>

using namespace std;

int use_uniform_move::create_a_triangle_with_glsl_uniform_move() {
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
                                   "uniform float move;\n"
                                   "void main(){\n"
                                   "  gl_Position = vec4(aPos.x + move, aPos.y, aPos.z, 1.0);\n"
                                   //                                     "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}\0";

  const char *fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "uniform vec4 ourColor;\n"
                                     "void main(){\n"
                                     "    FragColor = ourColor;\n"
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
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
  };

  unsigned int VAO_handle, VBO_handle;
  glGenVertexArrays(1, &VAO_handle);
  glGenBuffers(1, &VBO_handle);

  // ********************************************************************************
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  // 1.绑定 VAO_handle
  glBindVertexArray(VAO_handle);
  // 2.绑定 VBO_handle
  glBindBuffer(GL_ARRAY_BUFFER, VBO_handle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // 3.设置 Attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
  glEnableVertexAttribArray(0);
  // ********************************************************************************

  // note that this is allowed, the call to glVertexAttribPointer registered VBO_handle as the vertex attribute's bound vertex buffer object so afterward we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO_handle afterward so other VAO_handle calls won't accidentally modify this VAO_handle, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray , so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);


  float move = -1.5f;

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
//        draw_frame(shaderProgram, VAO_handle, move);

    // 设置调用 clear 所使用的颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // 清空屏幕
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

//        double timeValue = glfwGetTime();
//        double greenValue = fmod(timeValue, 1.0);
//
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        glUniform4f(vertexColorLocation, 0.0f, (float) greenValue, 0.0f, 1.0f);
    glUniform4f(vertexColorLocation, 0.0f, 0.5f, 0.0f, 1.0f);

    if (move >= 1.5f) {
      move = -1.5f;
    } else {
      move += 0.01f;
    }
    cout << "move:" << move << endl;

    int moveLocation = glGetUniformLocation(shaderProgram, "move");
    glUniform1f(moveLocation, move);

    // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO_handle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    // 交换 Buffer
    glfwSwapBuffers(window);

    // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    glfwPollEvents();
  }

  // 释放/删除之前的分配的所有资源
  glfwTerminate();
  return 0;
}

void use_uniform_move::init_glfw() {
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

GLFWwindow *use_uniform_move::create_glfw_window() {
  // Create a windows
  GLFWwindow *window = glfwCreateWindow(800, 800, "lucas_opengl", nullptr, nullptr);

  // Check if the window is created successfully
  if (window == nullptr) {
    std::cout << "failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  return window;
}

void use_uniform_move::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void use_uniform_move::check_shader(unsigned int shader, const std::string &type) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER:: " << type << " ::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void use_uniform_move::check_program(unsigned int shaderProgram) {
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    cout << "ERROR::shaderProgram::COMPILATION_FAILED\n" << infoLog << endl;
  }
}

void use_uniform_move::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
