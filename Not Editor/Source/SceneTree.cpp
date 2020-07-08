#include "SceneTree.h"
#include "NotEditor.h"
#include "ConfirmDialogue.h"
#include "NodeSpawner.h"
#include <Node.h>
#include <imgui.h>
#include <Scene.h>

void SceneTree::CreateTree(Node* node)
{
	mSelection.LoopIndex++;
	ImGuiTreeNodeFlags node_flags = 0 | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick
		| ImGuiTreeNodeFlags_SpanAvailWidth;
	bool isLeafNode = !node->GetChildrenCount();

	if (isLeafNode)
		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	mSelection.isSelected = (mSelection.selection_mask & (1 << mSelection.LoopIndex)) != 0;

	if (mSelection.isSelected)
		node_flags |= ImGuiTreeNodeFlags_Selected;

	bool isOpen = ImGui::TreeNodeEx((void*)(intptr_t)mSelection.LoopIndex, node_flags, node->GetNodeName().c_str());
	if (ImGui::IsItemClicked())
	{
		mSelection.SelectedNodeIndex = mSelection.LoopIndex;
		mSelection.node = node;
	}

	ImGui::SameLine(ImGui::GetWindowWidth() - 20);
	if (node->isVisible())
	{
		std::string V_ID = "V##" + std::to_string(mSelection.LoopIndex);
		if (ImGui::Button(V_ID.c_str()))
			node->Hide();
	}
	else
	{
		std::string H_ID = "H##" + std::to_string(mSelection.LoopIndex);
		if (ImGui::Button(H_ID.c_str()))
			node->Show();
	}

	if (isOpen)
	{
		for (Node* child : node->GetChildrens())
			CreateTree(child);
		if (!isLeafNode)
			ImGui::TreePop();
	}
}

SceneTree::SceneTree(NotEditor* Parent) : EditorComponents(Parent), mSelection(Parent->GetSelection())
{
}

SceneTree::~SceneTree()
{
}

void SceneTree::Ready()
{
}

void SceneTree::Render()
{
	static std::shared_ptr<NodeSpawner> Spawner = std::dynamic_pointer_cast<NodeSpawner>(mParent->GetUtility("NodeSpawner"));
	static std::shared_ptr<ConfirmDialogue> Confirmation = std::dynamic_pointer_cast<ConfirmDialogue>(mParent->GetUtility("ConfirmDialogue"));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

	ImGui::Begin("Scene Tree", nullptr);

	ImGui::Separator();
	if (ImGui::Button("Add (+)") && mSelection.node)
	{
		ImGui::OpenPopup("Node Spawner");
	}

	if (mSelection.node)
		Spawner->Render();

	ImGui::SameLine();
	if (ImGui::Button("Remove") && mSelection.node)
	{
		ImGui::OpenPopup("Confirm Action");
	}

	bool ConfirmationStatus = false;
	if (mSelection.node)
	{
		Confirmation->SetMessage("Are You Sure to Delete this Node ?");
		Confirmation->Render();
		ConfirmationStatus = Confirmation->GetStatus();
	}
	if (ConfirmationStatus)
		mSelection.node->DeleteSelf();

	ImGui::SameLine();
	char SearchBar[128] = "Search Nodes";
	ImGui::PushItemWidth(-1);
	ImGui::InputText("Search Nodes", SearchBar, IM_ARRAYSIZE(SearchBar));
	ImGui::PopItemWidth();
	ImGui::Separator();

	mSelection.SelectedNodeIndex = -1;
	mSelection.LoopIndex = -1;

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	CreateTree(mParent->GetActiveScene()->GetSceneRoot());

	if (mSelection.SelectedNodeIndex != -1)
	{
		//Implement Vector for multi select objects, and show property for Vec[0]
		if (ImGui::GetIO().KeyCtrl)
			mSelection.selection_mask ^= (1 << mSelection.SelectedNodeIndex);
		else
			mSelection.selection_mask = (1 << mSelection.SelectedNodeIndex);
	}

	ImGui::PopStyleVar();
	ImGui::End();
}
