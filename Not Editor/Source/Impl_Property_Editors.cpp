#include "..\..\Not Engine\Source\ColorRect.h"
#include "..\..\Not Engine\Source\ColorRect.h"
#include "..\..\Not Engine\Source\Node.h"
#include "..\..\Not Engine\Source\Node.h"
#include <Not Engine.h>
#include <imgui.h>
#include <imgui_stdlib.h>

void Node::PropertyEditor()
{
	static bool HeaderOpened = true;
	ImGui::SetNextItemOpen(HeaderOpened);
	if (ImGui::CollapsingHeader("Node"))
	{
		std::string tmp = Name;
		std::string sID = std::to_string(ID);
		ImGui::Text("ID :\t"); ImGui::SameLine(); ImGui::Text(sID.c_str());
		if (ImGui::InputText("Name", &tmp, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (tmp.size())
				Rename(std::move(tmp));
			else
				Rename("Unnamed Node");
		}
		ImGui::Checkbox("Visible", &Visible);
		HeaderOpened = true;
	}
	else
		HeaderOpened = false;
}

void Node2D::PropertyEditor()
{
	Node::PropertyEditor();

	static bool HeaderOpened = true;
	ImGui::SetNextItemOpen(HeaderOpened);
	if (ImGui::CollapsingHeader("Node2D"))
	{
		float tmpVec[2] = { Position.x, Position.y };

		if (ImGui::DragFloat2("Position", tmpVec, 0.01f))
			SetPosition(glm::vec2(tmpVec[0], tmpVec[1]));

		tmpVec[0] = Scale.x;
		tmpVec[1] = Scale.y;
		if (ImGui::DragFloat2("Scale", tmpVec, 0.01f))
			SetScale(glm::vec2(tmpVec[0], tmpVec[1]));
		tmpVec[0] = Rotation;
		if (ImGui::DragFloat("Rotate", tmpVec, 1.0f, -180.0f, 180.0f))
			SetRotation(tmpVec[0]);
		HeaderOpened = true;
	}
	else
		HeaderOpened = false;
}

void ColorRect::PropertyEditor()
{
	Node2D::PropertyEditor();

	static bool isNotCollapsed = true;
	ImGui::SetNextItemOpen(isNotCollapsed);
	if (ImGui::CollapsingHeader("ColorRect"))
	{
		ImGui::Checkbox("Transparent", &isTransparent);
		float tmpVec[4] = { RectColor.r, RectColor.g, RectColor.b, Alpha };
		if (ImGui::ColorEdit4("Color", tmpVec))
			SetColor(glm::vec4(tmpVec[0], tmpVec[1], tmpVec[2], tmpVec[3]));

		isNotCollapsed = true;
	}
	else
		isNotCollapsed = false;
}

void TextureRect::PropertyEditor()
{
	Node2D::PropertyEditor();

	static bool MatEditor = false, isNotCollapsed = true;

	ImGui::SetNextItemOpen(isNotCollapsed);
	if (ImGui::CollapsingHeader("Texture"))
	{
		isNotCollapsed |= true;
		ImTextureID TexPreview = (void*)TextureData->GetTextureID();
		ImVec2 PanelSize = ImVec2(ImGui::GetWindowSize().x * 0.6, ImGui::GetWindowSize().x * 0.6);
		ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - PanelSize.x) / 2, ImGui::GetCursorPos().y));

		if (ImGui::ImageButton(TexPreview, PanelSize, ImVec2(0, 1), ImVec2(1, 0), 2, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)))
			MatEditor ^= true;
	}
	else
		isNotCollapsed &= false;

	if (MatEditor)
	{
		ImGui::Checkbox("Transparent", &isTransparent);
	}
}

void Node3D::PropertyEditor()
{
	Node::PropertyEditor();
}