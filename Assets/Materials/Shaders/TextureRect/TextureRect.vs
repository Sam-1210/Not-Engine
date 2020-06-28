#version 440 core

layout (location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

uniform mat4 MVP;

out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = MVP * vec4(aPos, 0.0f, 1.0f);
};
