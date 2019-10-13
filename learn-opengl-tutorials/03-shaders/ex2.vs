#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; // color variable has attribute position 1
out vec3 vertexColor; // specity color output to the fragment shader
uniform float offset;
void main(){
     gl_Position = vec4(position.x + offset, position.y, position.z, 1.0);
     //vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
     vertexColor = color;
}
