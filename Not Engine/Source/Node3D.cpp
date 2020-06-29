#include "Node3D.h"

Node3D::Node3D() : Node("Node3D")
{
	this->Rotation = glm::vec3(0.0f);
	this->Position = glm::vec3(1.0f);
	this->Scale = glm::vec3(1.0f);
}

Node3D::Node3D(const std::string NodeName) : Node(NodeName)
{
	this->Rotation = glm::vec3(0.0f);
	this->Position = glm::vec3(1.0f);
	this->Scale = glm::vec3(1.0f);
}

Node3D::Node3D(const std::string NodeName, const bool& isVisible, const bool& isProcess)
	:Node(NodeName, isVisible, isProcess)
{
	this->Rotation = glm::vec3(0.0f);
	this->Position = glm::vec3(1.0f);
	this->Scale = glm::vec3(1.0f);
}
