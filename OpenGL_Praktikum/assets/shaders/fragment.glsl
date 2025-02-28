#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;

//light and material parameters
uniform vec3 lightPos; //light position
uniform vec3 lightColor; //light color
uniform vec3 viewPos; //cam position

out vec4 FragColor;

void main() {

    //ambient lighting
    float ambientIntensity = 0.1;
    vec3 ambient = ambientIntensity * lightColor;

    //Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular lighting
    float specularIntensity = 0.5;
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularIntensity * spec * lightColor;

    //lighting result here
    vec3 result = (ambient + diffuse + specular) * vertexColor;
    FragColor = vec4(result, 1.0); // RGB + alpha (1.0 for opaque)
}
