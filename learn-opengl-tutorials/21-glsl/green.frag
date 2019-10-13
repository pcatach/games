#version 330 core
//in vec2 TexCoords;

// input interface block
in VS_OUT
{
    vec2 TexCoords;
} fs_in;
// use: fs_in.TexCoords

out vec4 color;

uniform sampler2D texture1;

void main() {
     color = vec4(0.0, 1.0, 0.0, 1.0);
}
