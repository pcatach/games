#version 330 core
struct Material {
       sampler2D diffuse;
       sampler2D specular;
       float shininess;
};

struct Light {
    vec3 direction; // directional light
    vec3 position; //point light
    float cutOff; // spotlight
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // only for point light:
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    // cone of light
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // Diffuse
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // Attenuation (only for point light)
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic * (distance*distance));
    //ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}
