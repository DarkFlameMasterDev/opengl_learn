//
// Created by 曹璐韬 on 2023/8/12.
//

#include "2_two_VAO_two_VBO.h"
#include <iostream>


int two_VAO_two_VBO::create_two_triangle_with_two_VAO_two_VBO() {
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

  const char *fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main(){\n"
                                     "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\0";

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  check_shader(vertexShader, "GL_VERTEX_SHADER");

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  check_shader(fragmentShader, "GL_FRAGMENT_SHADER");

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  check_program(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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

    draw_frame_background(shaderProgram);
    draw_frame(shaderProgram, VAO[0]);
    draw_frame(shaderProgram, VAO[1]);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}


void two_VAO_two_VBO::init_glfw() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}


GLFWwindow *two_VAO_two_VBO::create_glfw_window() {
  GLFWwindow *window = glfwCreateWindow(800, 800, "lucas_opengl", nullptr, nullptr);

  if (window == nullptr) {
    std::cout << "failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  return window;
}

void two_VAO_two_VBO::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void two_VAO_two_VBO::check_shader(unsigned int shader, const string &type) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER:: " << type << " ::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void two_VAO_two_VBO::check_program(unsigned int shaderProgram) {
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    cout << "ERROR::shaderProgram::COMPILATION_FAILED\n" << infoLog << endl;
  }
}

/**
 * 关键在于这里，要将 glClear 和 绘制 VAO 分开，这样就不会在绘制多个 VAO 的时候，多次调用 glClear
 * @param shaderProgram
 */
void two_VAO_two_VBO::draw_frame_background(unsigned int shaderProgram) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(shaderProgram);
}

void two_VAO_two_VBO::draw_frame(unsigned int shaderProgram, unsigned int VAO) {

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

void two_VAO_two_VBO::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
