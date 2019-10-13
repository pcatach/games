#version 330 core
in vec3 vertexColor;
in vec2 TexCoord;

out vec4 color;

/*
sampler2D have the default value of the location active texture (0)
this location is known as texture unit
*/

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(){
     vec2 faceTexCoord = vec2(TexCoord.x, -1.0*TexCoord.y);
     color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, faceTexCoord), 0.2);
}
