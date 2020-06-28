#include "Node2D.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

void Node2D::PropertyEditor()
{
	Node::PropertyEditor();

	static bool HeaderOpened = true;
	ImGui::SetNextItemOpen(HeaderOpened);
	if (ImGui::CollapsingHeader("Node2D"))
	{
		float tmpVec[2] = { Position.x, Position.y };

		if (ImGui::DragFloat2("Position", tmpVec))
			SetPosition(glm::vec2(tmpVec[0], tmpVec[1]));

		tmpVec[0] = Scale.x;
		tmpVec[1] = Scale.y;
		if (ImGui::DragFloat2("Scale", tmpVec))
			SetScale(glm::vec2(tmpVec[0], tmpVec[1]));
		tmpVec[0] = glm::radians(Rotation);
		if (ImGui::SliderAngle("Rotate", tmpVec), -180.0f, 180.0f)
			SetRotation(glm::degrees(tmpVec[0]));
		HeaderOpened = true;
	}
	else
		HeaderOpened = false;
}
