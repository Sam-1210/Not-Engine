#include "Inspector.h"
#include "NotEditor.h"
#include <Node.h>
#include <imgui.h>

Inspector::Inspector(NotEditor* Parent) : EditorComponents(Parent), flags({true, 0, 0}), mSelection(Parent->GetSelection())
{
}

Inspector::~Inspector()
{
}

void Inspector::Ready()
{
}

void Inspector::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	ImGui::Begin("Inspector");

	flags.width = ImGui::GetWindowSize().x;
	flags.height = ImGui::GetWindowSize().y;

	if (mSelection.node)
		mSelection.node->PropertyEditor();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::End();
}
