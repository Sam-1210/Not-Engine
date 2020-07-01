#include "ColorRect.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

ColorRect::ColorRect() : Rect2D("ColorRect")
{
	mShader = Shader::Add("ColorRect");
	RectColor = glm::vec4(1.0);
}

ColorRect::ColorRect(const std::string& Name)
	: Rect2D(Name)
{
	mShader = Shader::Add("ColorRect");
	RectColor = glm::vec4(1.0);
}

ColorRect::ColorRect(const std::string& Name, const glm::vec4& Color)
	:Rect2D(Name)
{
	mShader = Shader::Add("ColorRect");
	RectColor = glm::vec3(Color);
	this->Alpha = Color.a;
}

void ColorRect::_process()
{
	Rect2D::_process();
}

void ColorRect::_update()
{
	Rect2D::_update();
}

void ColorRect::_render()
{
	mShader->Bind();
	glBindVertexArray(VAO);

	glm::mat4 MVP = Mat_Projection * Mat_View * Mat_Model;
	mShader->SetUniform("MVP", MVP);

	if (isTransparent)
	{
		mShader->SetUniform("Color", RectColor);
		mShader->SetUniform("Alpha", Alpha);
	}
	else
	{
		mShader->SetUniform("Color", RectColor);
		mShader->SetUniform("Alpha", 1.0f);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
