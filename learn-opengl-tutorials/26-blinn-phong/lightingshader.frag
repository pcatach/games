#version 330 core
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
     float ambientStrength = 0.1f;
     vec3 ambient = ambientStrength * lightColor;

     // when doing lighting calculations, make sure you always normalize the vectors
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos - FragPos);

     float diff = max(dot(norm, lightDir), 0.0); // make sure is never negative
     vec3 diffuse = diff * lightColor;

     float specularStrength = 0.5f;
     vec3 viewDir = normalize(viewPos - FragPos);
     //vec3 reflectDir = reflect(-lightDir, norm); // this function expects the first vector to point from the light source to the fragments position
     vec3 halfwayDir = normalize(lightDir + viewDir);

     int shininess = 1.0;
     float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
     ///32 is the shininess value of the highlight (controls the scatter of the specular)
     vec3 specular = specularStrength * spec * lightColor;

     vec3 result = (ambient + diffuse + specular) * objectColor;
     color = vec4(result, 1.0f);
}
