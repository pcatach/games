#version 330 core
in vec3 vertexColor; // input from the vertex shader (same name and type)
out vec4 color;
//uniform vec4 ourColor; // this way we can acess the color from outside the shader
void main(){
     //color = ourColor;
       color = vec4(vertexColor, 1.0);
}
