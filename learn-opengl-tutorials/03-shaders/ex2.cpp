#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "shader.h"

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

  GLFWwindow* window = glfwCreateWindow(800, 600, "03 Shaders", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, 800, 600);

  /*
  GLfloat vertices[] = {
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0
  };
  */
  GLfloat vertices[] = {
    // Positions         // Colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top
  };

  /*
    Although we only supplied 3 colors, fragment interpolation in the fragment shaders
    will produce much more fragments than vertices originally specified,
    the rasterizer then determines the position of those fragments and interpolates
    (linearly) the fragment shader's input variables
   */

  Shader ourShader("./ex2.vs", "./shader.frag");

  GLuint VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute (with offest of 3*sizeof(GLfloat)) to start after the position data
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);


  while (!glfwWindowShouldClose(window)){
    glfwPollEvents();

    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.Use();

    // change color over time
    GLfloat timeValue = glfwGetTime();
    GLfloat offsetValue = (sin (7*timeValue) / 2);
    // query ourColor location uniform
    GLint offsetLocation = glGetUniformLocation(ourShader.Program, "offset");
    // set the uniform. we need to use the program first, because it sets the uniform
    // on the currently active program
    glUniform1f(offsetLocation, offsetValue);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
  return 0;
}
