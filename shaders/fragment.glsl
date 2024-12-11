#version 460 core

in vec3 vertexColor;

out vec4 FragColor;

uniform float onTime;

void main()
{
    // FragColor = vec4(vertexColor + sin(onTime) * 0.25 + 0.25, 1.0);
    FragColor = vec4(vertexColor, 1.0);
} 