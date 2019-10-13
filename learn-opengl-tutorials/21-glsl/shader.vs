#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

//out vec2 TexCoords;

// interface block
out VS_OUT {
  vec2 TexCoords;
} vs_out;

//uniform block
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    //gl_PointSize = gl_Position.z;
    //vs_out.TexCoords = texCoords
}
