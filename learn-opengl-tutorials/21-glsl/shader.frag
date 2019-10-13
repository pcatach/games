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
    //if(gl_FragCoord.x < 400)
    if(gl_FrontFacing)
        color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    else
        color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
