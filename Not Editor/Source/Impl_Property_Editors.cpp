#include <Not Engine.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_stdlib.h>
#include "Editor.h"

void Node::PropertyEditor()
{
	static bool HeaderOpened = true;
	ImGui::SetNextItemOpen(HeaderOpened);
	if (ImGui::CollapsingHeader("Node"))
	{
		std::string tmp = Name;
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

	static bool isNotCollapsed = true;
	ImGui::SetNextItemOpen(isNotCollapsed);
	if (ImGui::CollapsingHeader("TextureRect"))
	{
		ImGui::Checkbox("Transparent", &isTransparent);
		isNotCollapsed = true;
		ImGui::Text("Preview Texture");
		ImTextureID TexPreview = (void*)TextureData->GetTextureID();
		ImVec2 PanelSize = ImVec2(Editor::GetInstance()->GetRightPanelWidth() * 0.8, Editor::GetInstance()->GetRightPanelWidth() * 0.8);
		ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - PanelSize.x) / 2, ImGui::GetCursorPos().y));
		if (ImGui::ImageButton(TexPreview, PanelSize, ImVec2(0, 1), ImVec2(1, 0), 2, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)))
		{ }
	}
	else
		isNotCollapsed = false;
}

void Node3D::PropertyEditor()
{
	Node::PropertyEditor();
}