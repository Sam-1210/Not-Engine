#include "Node2D.h"

Node2D::Node2D() : Node("Node2D")
{
	this->Rotation = 0.0f;
	this->Position = glm::vec2(0.0f);
	this->Scale = glm::vec2(1.0f, 1.0f);
}

Node2D::Node2D(const std::string NodeName) : Node(NodeName)
{
	this->Rotation = 0.0f;
	this->Position = glm::vec2(0.0f);
	this->Scale = glm::vec2(1.0f, 1.0f);
}

Node2D::Node2D(const std::string NodeName, const bool& isVisible, const bool& isProcess)
	:Node(NodeName, isVisible, isProcess)
{
	this->Rotation = 0.0f;
	this->Position = glm::vec2(0.0f);
	this->Scale = glm::vec2(1.0f, 1.0f);
}
