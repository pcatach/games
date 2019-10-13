#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 pos = projection * view * vec4(position, 1.0f);
    gl_Position = pos.xyww; // this way, the depth is always maximum and the skybox remains in the background
    TexCoords = position;
}
