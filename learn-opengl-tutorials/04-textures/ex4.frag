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
uniform float mixvalue;

void main(){
     //color = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);
     color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixvalue);
     // mix interpolate between the textures based in the 3rd argument
     // in this case there will be 80% of the 1st texture and 20% of the second
}
