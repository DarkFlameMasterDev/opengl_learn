//
// Created by 曹璐韬 on 2023/8/1.
//
#include <iostream>

#include "hello_window.h"


int hello_window::create_a_window() {

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

  // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
  //set the Viewport
  glViewport(0, 0, 400, 400);

  // 注册 framebuffer_size_callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    draw_frame();

    // 交换 Buffer
    glfwSwapBuffers(window);

    // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    glfwPollEvents();
  }

  // 释放/删除之前的分配的所有资源
  glfwTerminate();
  return 0;
}

GLFWwindow *hello_window::create_glfw_window() {// Create a windows
  GLFWwindow *window = glfwCreateWindow(800, 800, "lucas_opengl", nullptr, nullptr);

  // Check if the window is created successfully
  if (window == nullptr) {
    std::cout << "failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  return window;
}

void hello_window::init_glfw() {
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

void hello_window::draw_frame() {

  // 设置调用 clear 所使用的颜色
  glClearColor(.2f, .3f, .3f, 1.f);

  // 清空屏幕
  glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * 检测是否有按键输入
 * 如果按下了 esc 就设置当前窗口应该退出
 * @param window
 */
void hello_window::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

/**
 * 回调函数，在窗口大小调整的时候，调整 ViewPort 的大小
 * @param window
 * @param width
 * @param height
 */
void hello_window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}