#include "ConfirmDialogue.h"
#include "NotEditor.h"
#include <imgui.h>

ConfirmDialogue::ConfirmDialogue(NotEditor* Parent) 
	: EditorComponents(Parent), mStatus(false), mMessage(nullptr)
{
}

ConfirmDialogue::~ConfirmDialogue()
{
}

void ConfirmDialogue::Ready()
{
}

void ConfirmDialogue::Render()
{
	if (ImGui::BeginPopupModal("Confirm Action", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(mMessage);
		ImGui::Separator();

		if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); mStatus = true; }

		ImGui::SetItemDefaultFocus();

		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); mStatus = false; }
		ImGui::EndPopup();
	}
}
