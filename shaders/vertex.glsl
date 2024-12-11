#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;

void main()
{
    vertexColor = aPos;
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}