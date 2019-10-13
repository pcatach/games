#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

using namespace std;

class Shader{
  public:
  // Program ID
  GLuint Program;

  Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
    // 1) get the source code;
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    // ensure ifstreams can throw exceptions;
    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);

    try{
      // open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // convert stream to GLchar[]
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    } catch(ifstream::failure e){
      cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // 2) compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[521];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Debug
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    };

    // Similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Debug
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    };

    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if(!success){
      glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
      cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  // use the program
  void Use(){
    glUseProgram(this->Program);
  }

};

#endif
