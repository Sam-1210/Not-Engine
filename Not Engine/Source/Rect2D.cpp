#include "Rect2D.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


bool Rect2D::BuffersSet = false;
unsigned int Rect2D::VBO;
unsigned int Rect2D::VAO;

float Rect2D::vertices[24] = {
	0.5f,  0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f, 1.0f,

	0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f, 1.0f
};

void Rect2D::SetBuffers()
{
	if (BuffersSet)
		return;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	BuffersSet = true;
}

Rect2D::Rect2D(const std::string NodeName) : Node2D(NodeName)
{
	isTransparent = true;

	SetBuffers();

	//glm::vec2 ViewportSize = Application::ActiveApplication->GetViewportSize();
	float AspectRatio = 1280 / 720;
	Mat_Projection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	Mat_View = glm::mat4(1.0f);
	Mat_Model = glm::translate(glm::mat4(1.0f), glm::vec3(this->Position, 0.0f));
}

Rect2D::~Rect2D()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Rect2D::_process()
{
}

void Rect2D::_update()
{
	//glm::vec2 ViewportSize = Application::ActiveApplication->GetViewportSize();
	float AspectRatio = 1280 / 720;
	Mat_Projection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	Mat_Model = glm::mat4(1.0f);
	Mat_Model = glm::translate(Mat_Model, glm::vec3(this->Position, 0.0f));
	Mat_Model = glm::rotate(Mat_Model, glm::radians(this->Rotation), glm::vec3(0.0, 0.0, 1.0));
	Mat_Model = glm::scale(Mat_Model, glm::vec3(this->Scale, 1.0f));

	static float u = 0.0f, r = 0.0f, speed = 0.002f, scale = 1.0f;

	//if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_W) == GLFW_PRESS)
	//	u -= speed;
	//if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_S) == GLFW_PRESS)
	//	u += speed;
	//if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_D) == GLFW_PRESS)
	//	r -= speed;
	//if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_A) == GLFW_PRESS)
	//	r += speed;
	//if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_DOWN) == GLFW_PRESS)
	//	if (scale > 0.4f)
	//		scale -= speed;
	//if (glfwGetKey(Application::ActiveApplication->GetWindowObject(), GLFW_KEY_UP) == GLFW_PRESS)
	//	if (scale < 1.0f)
	//		scale += speed;

	Mat_View = glm::mat4(1.0f);
	Mat_View = glm::translate(Mat_View, glm::vec3(r, u, 0.0));
	Mat_View = glm::scale(Mat_View, glm::vec3(scale));
}
