#include "NodeSpawner.h"
#include "NotEditor.h"
#include <Not Engine.h>
#include <imgui.h>

NodeSpawner::NodeSpawner(NotEditor* Parent)
	: EditorComponents(Parent)
{
}

NodeSpawner::~NodeSpawner()
{
}

void NodeSpawner::Ready()
{
}

void NodeSpawner::Render()
{
	bool Close = true;
	char SearchBox[128] = "Node Type";
	Application* App = mParent->GetApp();
	Node* Parent = mParent->GetSelection().node;

	ImGui::SetNextWindowSize(ImVec2(400.0f, App->GetHeight() - 400.0f));

	if (ImGui::BeginPopupModal("Node Spawner", &Close))
	{
		ImGui::Text("Search");

		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("Node"))
		{
			ImGui::SameLine(ImGui::GetWindowWidth() - 50);
			if (ImGui::Button("Add##"))
				Parent->AddChild(new Node());

			ImGui::SetNextItemOpen(true);
			if (ImGui::TreeNode("Node2D"))
			{
				ImGui::SameLine(ImGui::GetWindowWidth() - 50);
				if (ImGui::Button("Add##"))
					Parent->AddChild(new Node2D());

				ImGui::SetNextItemOpen(true);
				if (ImGui::TreeNode("ColorRect"))
				{
					ImGui::SameLine(ImGui::GetWindowWidth() - 50);
					if (ImGui::Button("Add##"))
						Parent->AddChild(new ColorRect());
					ImGui::TreePop();
				}
				ImGui::SetNextItemOpen(true);
				if (ImGui::TreeNode("TextureRect"))
				{
					ImGui::SameLine(ImGui::GetWindowWidth() - 50);
					if (ImGui::Button("Add##"))
						Parent->AddChild(new TextureRect());
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		//ImGui::PushItemWidth(-1);
		//ImGui::InputText("Add Node Search", SearchBox, IM_ARRAYSIZE(SearchBox));
		//ImGui::PopItemWidth();

		ImGui::EndPopup();
	}
}
