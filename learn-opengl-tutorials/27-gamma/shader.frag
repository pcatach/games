#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture1;

void main() {
    color = texture(texture1, TexCoords);

    // gamma correction
    float gamma = 2.2;
    color.rgb = pow(color.rgb, vec3(1.0/gamma));
}
