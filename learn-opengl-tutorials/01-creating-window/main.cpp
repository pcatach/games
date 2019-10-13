// -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "01 Create Window", nullptr, nullptr);
  if (window == nullptr) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  } else {
    cout << "GLFW window created" << endl;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE; // ensure GLEW use core profile
  if (glewInit() != GLEW_OK){
    cout << "Failed to initialize GLEW" << endl;
    return -1;
  } else {
    cout << "GLEW initialized" << endl;
  }

  glViewport(0, 0, 800, 600); // the rendering area could be smaller than the GLFW window

  // game loop
  while (!glfwWindowShouldClose(window)){
    glfwPollEvents();

    // rendering commands here
    glClearColor(0.2, 0.3, 0.3, 1.0); // set the state
    glClear(GL_COLOR_BUFFER_BIT); // use the state

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
