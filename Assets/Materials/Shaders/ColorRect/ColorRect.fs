#version 440 core

out vec4 FragColor;

uniform vec3 Color;
uniform float Alpha;

void main()
{
   FragColor = vec4(Color, Alpha);
}