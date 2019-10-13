#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// our vertex shader...
const GLchar* vertex_shader_source =
  "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "void main(){\n"
      "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
  "}";

// our fragment shader...
const GLchar* fragment_shader_source =
  "#version 330 core\n"
  "out vec4 color;"
  "void main(){\n"
      "color = vec4(0.2, 0.7, 1.0, 1.0);\n"
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

  GLFWwindow* window = glfwCreateWindow(800, 600, "02 Triangle", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  glViewport(0, 0, 800, 600);

  // the triangle's vertices
  GLfloat vertices[] = {
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0
  };

  // compile the shader's source code
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertexShader);
  /* to debug shader compilation:
     GLint success;
     GLchar infoLog[512];
     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
     if(!success)
     {
     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
     cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
     }
   */

  // compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragmentShader);

  // create shader program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  /* to debug:
     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
     if(!success) {
     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
     ...
     }
  */
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // now we just need to draw the triangle! we do that with a VAO (vertex array object), which sets the state to draw our objects
  GLuint VAO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  // a VBO (vertex buffer object) stores the vertices in the GPU's memory
  GLuint VBO; // the buffer will thave this unique ID that we can reference later
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer to the target GL_ARRAY_BUFFER (the buffer type for a vertex buffer object)
  //from now on, every call on GL_ARRAY_BUFFER will take effect on our VBO buffer
  // this next function copies the vertex data into the buffer's memory
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  /* GL_STATIC_DRAW: the data won't probably change a lot
   * GL_DYNAMIC_DRAW: is likely to change a lot
   * GL_STREAM_DRAW: will change every time it is drawn
   */

  // now we need to tell OpenGL how to interpret the vertex data and connect it to vertex shader's attributes
  /* 1st param: which vertex attribute to configure (in vertex shader we have layout(location=0))
   * 2nd param: size of vertex attribute
   * 3rd param: type of data
   * 4th param: if we want the data normalized
   * 5th param: stride (the space between vertex attribute sets)
   * 6th param: offset of the data in the buffer
   */
  // the VBO which the vertex attribute takes its data from is determined by the VBO currently bound to GL_ARRAY_BUFFER
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);


  while (!glfwWindowShouldClose(window)){
    glfwPollEvents();

    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
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
