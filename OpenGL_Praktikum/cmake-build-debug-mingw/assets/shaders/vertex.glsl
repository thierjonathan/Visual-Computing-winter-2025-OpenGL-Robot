#version 330 core

layout (location = 0) in vec3 pos; // Vertex position (x,y,z)
layout (location = 1) in vec3 colorRGB;

uniform mat4 model; //transformation matrix
uniform mat4 view;
uniform mat4 projection;

out vec3 colorVS;

void main(){
    colorVS = colorRGB;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}
