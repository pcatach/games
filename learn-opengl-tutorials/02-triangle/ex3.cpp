#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const GLchar* vertex_shader_source =
  "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "void main(){\n"
      "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
  "}";

const GLchar* fragment_shader_source1 =
  "#version 330 core\n"
  "out vec4 color;"
  "void main(){\n"
      "color = vec4(0.2, 0.7, 1.0, 1.0);\n"
  "}";

const GLchar* fragment_shader_source2 =
  "#version 330 core\n"
  "out vec4 color;"
  "void main(){\n"
      "color = vec4(1.0, 1.0, 0.0, 1.0);\n"
  "}";

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

  GLFWwindow* window = glfwCreateWindow(800, 600, "02 Triangles", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, 800, 600);

  GLfloat vertices1[] = {
    0.0, -0.5, 0.0,
    1.0, -0.5, 0.0,
    0.5, 0.5, 0.0,
  };
  GLfloat vertices2[] = {
    -1.0, -0.5, 0.0,
    0.0, -0.5, 0.0,
    -0.5, 0.5, 0.0
  };

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader1, 1, &fragment_shader_source1, NULL);
  glCompileShader(fragmentShader1);

  GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2, 1, &fragment_shader_source2, NULL);
  glCompileShader(fragmentShader2);

  GLuint shaderProgram1 = glCreateProgram();
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);

  GLuint shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader1);
  glDeleteShader(fragmentShader2);

  GLuint VAO1;
  glGenVertexArrays(1, &VAO1);

  glBindVertexArray(VAO1);

  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint VAO2;
  glGenVertexArrays(1, &VAO2);

  glBindVertexArray(VAO2);

  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  while (!glfwWindowShouldClose(window)){
    glfwPollEvents();

    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram1);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO1);

  glDeleteVertexArrays(1, &VAO2);
  glDeleteBuffers(1, &VBO2);

  glfwTerminate();
  return 0;
}
