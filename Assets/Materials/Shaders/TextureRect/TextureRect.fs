#version 440 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D Texture;
uniform float Color;

void main()
{
	if(Color == 1.0f)
		FragColor = vec4(Color);
	else
		FragColor = texture(Texture, TexCoords);
}