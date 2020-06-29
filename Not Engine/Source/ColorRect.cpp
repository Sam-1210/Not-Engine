#include "ColorRect.h"
#include "Shader.h"
#include "Application.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

ColorRect::ColorRect() : Rect2D("ColorRect")
{
	ColorShader = Shader::Add("ColorRect");
	RectColor = glm::vec4(1.0);
}

ColorRect::ColorRect(const std::string& Name)
	: Rect2D(Name)
{
	ColorShader = Shader::Add("ColorRect");
	RectColor = glm::vec4(1.0);
}

ColorRect::ColorRect(const std::string& Name, const glm::vec4& Color)
	:Rect2D(Name)
{
	ColorShader = Shader::Add("ColorRect");
	RectColor = Color;
}

void ColorRect::_process()
{
}

void ColorRect::_update()
{
	static float u = 0.0f, r = 0.0f, speed = 0.002f, scale = 1.0f;

	glm::vec2 ViewportSize = Application::ActiveApplication->GetViewportSize();
	float AspectRatio = ViewportSize.x / ViewportSize.y;
	Mat_Projection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	Mat_Model = glm::mat4(1.0f);
	Mat_Model = glm::translate(Mat_Model, glm::vec3(this->Position, 0.0f));
	Mat_Model = glm::rotate(Mat_Model, glm::radians(this->Rotation), glm::vec3(0.0, 0.0, 1.0));
	Mat_Model = glm::scale(Mat_Model, glm::vec3(this->Scale, 1.0f));

	if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_W) == GLFW_PRESS)
		u -= speed;
	if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_S) == GLFW_PRESS)
		u += speed;
	if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_D) == GLFW_PRESS)
		r -= speed;
	if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_A) == GLFW_PRESS)
		r += speed;
	if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_DOWN) == GLFW_PRESS)
		if(scale > 0.4f)
			scale -= speed;
	if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_UP) == GLFW_PRESS)
		if (scale < 1.0f)
			scale += speed;

	Mat_View = glm::mat4(1.0f);
	Mat_View = glm::translate(Mat_View, glm::vec3(r,u,0.0));
	Mat_View = glm::scale(Mat_View, glm::vec3(scale));
}

void ColorRect::_render()
{
	if (isTransparent)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);

	ColorShader->Bind();
	glBindVertexArray(VAO);

	glm::mat4 MVP = Mat_Projection * Mat_View * Mat_Model;

	ColorShader->SetUniform("MVP", MVP);
	ColorShader->SetUniform("Color", RectColor);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
