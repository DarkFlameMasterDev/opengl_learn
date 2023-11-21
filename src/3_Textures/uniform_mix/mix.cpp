//
// Created by 曹璐韬 on 2023/9/18.
//

#include "mix.h"
#include <iostream>
#include "Shader.h"

#define  STB_IMAGE_STATIC
#define  STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

using namespace std;

float mix::mixValue = 0.3f;

int mix::create_a_triangle_with_mix_textures() {

  init_glfw();
  GLFWwindow *window = create_glfw_window();
  if (window == nullptr) {
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    cout << "failed to initialize GLAD" << endl;
    glfwTerminate();
    return -1;
  }
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  string vertexPath = FileSystem::getPath("src/3_Textures/texture_vs.glsl");
  cout << "vertexPath: " << vertexPath << endl;
  string fragmentPath = FileSystem::getPath("src/3_Textures/uniform_mix/mix_fs.glsl");
  cout << "fragmentPath: " << fragmentPath << endl;

  Shader ourShader(vertexPath.c_str(), fragmentPath.c_str());


  float vertices[] = {
      // positions // colors // texture coords
      0.5f, 0.5f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, // top right

      0.5f, -0.5f, 0.0f,
      0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, // bottom right

      -0.5f, -0.5f, 0.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, // bottom left

      -0.5f, 0.5f, 0.0f,
      1.0f, 1.0f, 0.0f,
      0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture coords attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);


  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  unsigned int texture1, texture2;

  // texture1
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;

  stbi_set_flip_vertically_on_load(true);

  unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/wood.jpeg").c_str(), &width, &height,
                                  &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture1" << endl;
  }
  stbi_image_free(data);

  // texture2
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load(
      FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width,
      &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    cout << "Failed to load texture2" << endl;
  }
  stbi_image_free(data);

  ourShader.use();
  glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
  ourShader.setInt("texture2", 1);


  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    ourShader.setFloat("mixValue", getMixValue());

    ourShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    // 交换 Buffer
    glfwSwapBuffers(window);

    // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // 释放/删除之前的分配的所有资源
  glfwTerminate();
  return 0;
}


/**
 * initialize glfw
 */
void mix::init_glfw() {
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
GLFWwindow *mix::create_glfw_window() {
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
void mix::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

/**
 * 检测是否有按键输入
 * 如果按下了 esc 就设置当前窗口应该退出
 * @param window
 */
void mix::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    setMixValue(getMixValue() + 0.01f);
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    setMixValue(getMixValue() - 0.01f);
  }
}

void mix::check_shader(unsigned int shader, const string &type) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER:: " << type << " ::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void mix::check_program(unsigned int shaderProgram) {
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    cout << "ERROR::shaderProgram::COMPILATION_FAILED\n" << infoLog << endl;
  }
}

void mix::setMixValue(float value) {
  if (value < 0) {
    mix::mixValue = 0.0f;
    return;
  } else if (value > 1) {
    mix::mixValue = 1.0f;
    return;
  }
  mix::mixValue = value;
  cout << "a = " << mix::mixValue << endl;
}

float mix::getMixValue() {
  return mix::mixValue;
}
