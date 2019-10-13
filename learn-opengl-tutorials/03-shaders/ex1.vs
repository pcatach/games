#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; // color variable has attribute position 1
out vec3 vertexColor; // specity color output to the fragment shader
void main(){
     gl_Position = vec4(position.x, -1.0*position.y, position.z, 1.0); // invert triangle
     //vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
     vertexColor = color;
}
