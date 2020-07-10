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

void Node2D::Save(std::ofstream& SceneFile)
{
	SceneFile << "Node2D ";
	if (Parent)
		SceneFile << Parent->GetID() << " ";
	SceneFile << Name << " ";
	SceneFile << ID << " ";
	SceneFile << Visible << " ";
	SceneFile << Rotation << " ";
	SceneFile << Position.x << " " << Position.y << " ";
	SceneFile << Scale.x << " " << Scale.y;
	SceneFile << "\n";
}
void Node2D::Load(std::ifstream& SceneFile)
{
	Node::Load(SceneFile);
	SceneFile >> Rotation >> Position.x >> Position.y >> Scale.x >> Scale.y;
}
