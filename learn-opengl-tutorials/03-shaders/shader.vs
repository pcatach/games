/* shader structure (GLSL)

in type in_variable_name;
out type out_variable_name;
uniform type uniform_name;

void main(){
  .......
  out_variable_name = processed_stuff;
}

input variables: vertex attributes
there is a maximum number of vertex attributes (at least 16 4-component vertex attributes are available)

vecn : vector type with n floats (n=1,2,3,4)
bvecn: " booleans
ivecn: " integers
etc

vector components: vec.x, vec.y, vec.z, vec.w, vec.rgba, vec.stpq (texture coordinates)

swizzling:
vec2 a;
vec4 b = a.xyxx;

vectors as arguments:
vec2 a = vec2(0.5, 0.7);
vec4 b = vec4(a, 0.0, 0.0);

the vertex shader recieves its input straight from the vertex data
so we need to specify location metadata, fot this the layout (location=0)

uniforms: global variables (unique per shader program object)
we can define them in any shader we'd like
they are good to interchange data between your application and shaders

*/

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; // color variable has attribute position 1
out vec3 vertexColor; // specity color output to the fragment shader
void main(){
     gl_Position = vec4(position, 1.0);
     //vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
     vertexColor = color;
}
