#include <glad/gl.h>
#
#include <GLFW/glfw3.h>

#include <iostream>

int main() {
  if (!glfwInit()) {
    std::cerr << "GLFW failed to init\n";
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(800, 600, "GLAD v2 works!", nullptr, nullptr);
  if (!window) {
    std::cerr << "GLFW window creation failed\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "Glad failed to load OpenGL\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  std::cout << "OpenGL version loaded: " << glGetString(GL_VERSION) << "\n";

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}