#version 330 core

layout (location = 0) in vec3 pos; // Vertex position (x,y,z)
layout (location = 1) in vec3 initNormal; //Normal
layout (location = 2) in vec3 colorRGB;

uniform mat4 model; //transformation matrix
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec3 FragPos; //position in world coordinate system
out vec3 Normal; //the normal

void main(){
    FragPos = vec3(model * vec4(pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * initNormal; //transformed normal
    vertexColor = colorRGB;

    gl_Position = projection * view * model * vec4(pos, 1.0);
}
