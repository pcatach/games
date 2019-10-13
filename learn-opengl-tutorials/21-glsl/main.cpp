// Std. Includes
#include <string>
#include <map>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "shader.h"
#include "camera.hpp"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL/SOIL.h>

// Properties
GLuint screenWidth = 800, screenHeight = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
GLuint loadTexture(GLchar* path);
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// The MAIN function, from here we start our application and run our Game loop
int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "19 Framebuffer", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Setup and compile our shaders
    Shader shaderRed("./shader.vs", "./red.frag");
    Shader shaderGreen("./shader.vs", "./green.frag");
    Shader shaderBlue("./shader.vs", "./blue.frag");
    Shader shaderYellow("./shader.vs", "./yellow.frag");

    GLfloat cubeVertices[] = {
      // Back face
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
      // Front face
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
      // Left face
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
      // Right face
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
      // Bottom face
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
      // Top face
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
    };

    // Setup cube VAO
    GLuint cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);

    GLuint uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.Program, "Matrices");
    GLuint uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.Program, "Matrices");
    GLuint uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.Program, "Matrices");
    GLuint uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.Program, "Matrices");

    glUniformBlockBinding(shaderRed.Program, uniformBlockIndexRed, 0);
    glUniformBlockBinding(shaderGreen.Program, uniformBlockIndexGreen, 0);
    glUniformBlockBinding(shaderBlue.Program, uniformBlockIndexBlue, 0);
    glUniformBlockBinding(shaderYellow.Program, uniformBlockIndexYellow, 0);

    // uniform buffer
    GLuint uboMatrices;
    glGenBuffers(1, &uboMatrices);

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // fill buffer
    glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glm::mat4 view = camera.GetViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Game loop
    while(!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw objects
        glBindVertexArray(cubeVAO);

        shaderRed.Use();
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));  // Move top-left
        glUniformMatrix4fv(glGetUniformLocation(shaderRed.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderGreen.Use();
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));  // Move top-right
        glUniformMatrix4fv(glGetUniformLocation(shaderGreen.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderBlue.Use();
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));  // Move bottom-left
        glUniformMatrix4fv(glGetUniformLocation(shaderBlue.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderYellow.Use();
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));  // Move bottom-right
        glUniformMatrix4fv(glGetUniformLocation(shaderYellow.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// This function loads a texture from file. Note: texture loading functions like these are usually
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio).
// For learning purposes we'll just define it as a utility function.
GLuint loadTexture(GLchar* path)
{
    //Generate texture ID and load texture data
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); // prevent alpha interpolation on the borders
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;

}

GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil){
  GLenum attachment_type;
  if(!depth && !stencil)
    attachment_type = GL_RGB;
  else if(depth && !stencil)
    attachment_type = GL_DEPTH_COMPONENT;
  else if (!depth && stencil)
    attachment_type = GL_STENCIL_INDEX;

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  if(!depth && !stencil)
    glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, screenWidth, screenHeight, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  return textureID;
}

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
