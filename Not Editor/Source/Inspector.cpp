#include "Inspector.h"
#include "NotEditor.h"
#include <Node.h>
#include <imgui.h>

Inspector::Inspector(NotEditor* Parent) : EditorComponents(Parent), mSelection(Parent->GetSelection())
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

	ImGui::Begin("Property Editor", nullptr);
	if (mSelection.node)
		mSelection.node->PropertyEditor();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::End();
}
