#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class application {
 public:
  application() {}
  virtual ~application() {}

 public:
  virtual void run() {
    bool is_run = true;

    if (!glfwInit()) {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 768, "OPENGL EXAMPLE", NULL, NULL);
    if (window == NULL) {
      fprintf(stderr, "Failed to open GLFW window\n");
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      glfwTerminate();
      return;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    startup();

    do {
      render(glfwGetTime());

      glfwSwapBuffers(window);
      glfwPollEvents();

      is_run = (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0);
    } while (is_run);

    shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
  }

  virtual void render(double current_time) {}
  virtual void startup() {}
  virtual void shutdown() {}

 private:
  GLFWwindow* window;
};

#define DECLARE_MAIN(a)                   \
  int main(int argc, const char** argv) { \
    a* app = new a;                       \
    app->run();                           \
    delete app;                           \
    return 0;                             \
  }
