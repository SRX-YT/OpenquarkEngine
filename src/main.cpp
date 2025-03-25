#include <cstddef>
#include <iostream>
#include "../lib/glew/include/GL/glew.h"
#include "../lib/glfw/include/GLFW/glfw3.h"
#include "include/file_manager.h"

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // Init GLFW and configure
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLFW window creation
  GLFWwindow* window;
  window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // GLEW init
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  // Compiling a vertex shader
  // Store source code shader in string
  const char *vertexShaderSource = FileManager::readShaderFile("../../src/shaders/simpleVertexShader.glsl").c_str();
  // Create shader object
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // Attach shader source code to the shader object and compile
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // Check success of compilng
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Compiling a fragment shader
  // Store source code shader in string
  const char *fragmentShaderSource = FileManager::readShaderFile("../../src/shaders/simpleFragmentShader.glsl").c_str();
  // Create shader object
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // Attach shader srouce code to the shader object and compile
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // Check success of compiling
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Shader program
  // Creating a program object
  unsigned int shaderProgram = glCreateProgram();
  // Attach compiled shaders to the program object and link
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // Check success of linking
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINKING::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // Clear used shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Triangle vertices
  float vertices[] = {
      0.5f,  0.5f,  0.0f,
      0.5f, -0.5f,  0.0f,
     -0.5f, -0.5f,  0.0f,
     -0.5f, 0.5f, 0.0f
  };
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Bind VAO first, then bind and set vertex buffers and configure
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
