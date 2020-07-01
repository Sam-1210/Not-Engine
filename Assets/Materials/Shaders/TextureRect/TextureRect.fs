#version 440 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D Texture;
uniform int Transparent;

void main()
{	
	vec4 RectTex = texture(Texture, TexCoords);
	
	if(Transparent == 1)
		FragColor = RectTex;
	else
		if(RectTex.r == 0.0f && RectTex.g == 0.0f && RectTex.b == 0.0f && RectTex.a == 0.0f)
			FragColor = vec4(1.0f);
		else
			FragColor = vec4(vec3(RectTex), 1.0f);
}