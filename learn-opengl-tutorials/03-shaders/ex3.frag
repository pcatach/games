#version 330 core
in vec3 vertexColor; // input from the vertex shader (same name and type)
out vec4 color;

void main(){
       color = vec4(vertexColor, 1.0);
}
