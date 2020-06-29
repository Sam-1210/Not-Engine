#include "Rect2D.h"
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Application.h"


bool Rect2D::BuffersSet = false;
unsigned int Rect2D::ID;
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
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
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

	glm::vec2 ViewportSize = Application::ActiveApplication->GetViewportSize();
	float AspectRatio = ViewportSize.x / ViewportSize.y;
	Mat_Projection = glm::ortho(-1.0f * AspectRatio, 1.0f * AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	Mat_View = glm::mat4(1.0f);
	Mat_Model = glm::translate(glm::mat4(1.0f), glm::vec3(this->Position, 0.0f));
}

Rect2D::~Rect2D()
{
}

void Rect2D::_process()
{
}

void Rect2D::_update()
{
}

void Rect2D::_render()
{
}
