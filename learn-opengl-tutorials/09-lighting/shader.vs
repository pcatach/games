#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main(){
     gl_Position = projection * view * model * vec4(position, 1.0);
     FragPos = vec3(model * vec4(position, 1.0f)); // we want it in world coordinates
     //Normal = normal; // as normals are normalized, they only specify directions and are not affected by translations, thats why we dont need to model translate them, however, if we need to scale and rotate them, we use the normal matrix
     Normal = mat3(transpose(inverse(model))) * normal;
     // AVOID INVERTING MATRICES!! $$$$ (prefer to do this in the CPU)
}
