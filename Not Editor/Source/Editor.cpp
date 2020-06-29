#include "Editor.h"
#include <Not Engine.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <filesystem>


Editor* Editor::Instance = nullptr;

struct SceneTreeSelectedNode
{
	bool isSelected;
	int selection_mask;
	int LoopIndex;
	int SelectedNodeIndex;
	Node* node;
};

SceneTreeSelectedNode Editor::SelectedNode;

void Editor::DrawTreeStructure(Node* node)
{
	SelectedNode.LoopIndex++;
	ImGuiTreeNodeFlags node_flags = 0 | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick
		| ImGuiTreeNodeFlags_SpanAvailWidth;
	bool isLeafNode = !node->GetChildrenCount();

	if(isLeafNode)
		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	SelectedNode.isSelected = (SelectedNode.selection_mask & (1 << SelectedNode.LoopIndex)) != 0;

	if (SelectedNode.isSelected)
		node_flags |= ImGuiTreeNodeFlags_Selected;

	bool isOpen =  ImGui::TreeNodeEx((void*)(intptr_t)SelectedNode.LoopIndex, node_flags, node->GetNodeName().c_str());
	if (ImGui::IsItemClicked())
	{
		SelectedNode.SelectedNodeIndex = SelectedNode.LoopIndex;
		SelectedNode.node = node;
	}

	ImGui::SameLine(ImGui::GetWindowWidth() - 20);
	if (node->isVisible())
	{
		std::string V_ID = "V##" + std::to_string(SelectedNode.LoopIndex);
		if (ImGui::Button(V_ID.c_str()))
			node->Hide();
	}
	else
	{
		std::string H_ID = "H##" + std::to_string(SelectedNode.LoopIndex);
		if (ImGui::Button(H_ID.c_str()))
			node->Show();
	}

	if (isOpen)
	{
		for (Node* child : node->GetChildrens())
			DrawTreeStructure(child);
		if (!isLeafNode)
			ImGui::TreePop();
	}
}

Editor::Editor(const bool& EditMode, Application* App)
{
	this->Editable = EditMode;
	this->Theme = 1;
	this->App = App;
	SelectedNode.selection_mask = 0;

	CurrentScene = nullptr;
	MainMenuBarHeight = 19;
	MinColumnWidth = App->GetWindowSize().x * 0.2;
	MaxColumnWidth = App->GetWindowSize().x * 0.3;
	LPW = MinColumnWidth;
	RPW = MinColumnWidth;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle();
	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	std::string EditorFontPath = EnginePath::FontsFolder + "Editor_Default.ttf";
	if (std::filesystem::exists(EditorFontPath))
		EditorFont = io->Fonts->AddFontFromFileTTF(EditorFontPath.c_str(), 18);
	else
		EditorFont = nullptr;

	ImGui_ImplGlfw_InitForOpenGL(App->GetWindowObject(), true);
	ImGui_ImplOpenGL3_Init();

	ChangeTheme(Theme);
	NE_CORE_INFO("All Processes of Editor Started Successfully");
}

Editor* Editor::InitialiseEditor(const bool& EditMode, Application* App)
{
	if (!Instance)
		Instance = new Editor(EditMode, App);
	return Instance;
}

Editor* Editor::GetInstance()
{
	return Instance;
}

Editor::~Editor()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	NE_CORE_INFO("Editor Shutdown");
}

float Editor::GetMainMenuBarHeight()
{
	return MainMenuBarHeight;
}

float Editor::GetLeftPanelWidth()
{
	return LPW;
}

float Editor::GetRightPanelWidth()
{
	return RPW;
}

void Editor::SetContext(Application* ApplicationContext)
{
}

void Editor::SetEditMode(const bool& EditMode)
{
	Editable = EditMode;
}

void Editor::ChangeTheme(const bool& Theme)
{
	this->Theme = Theme;
	if(Theme)
		ImGui::StyleColorsLight();
	else
		ImGui::StyleColorsDark();
}

void Editor::Frame(Scene* scene)
{
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	//window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	//window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	//static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	//if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	//	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	
	if (!Editable)
		return;
	if (!scene)
		return;
	
	MinColumnWidth = App->GetWindowSize().x * 0.2;
	MaxColumnWidth = App->GetWindowSize().x * 0.3;

	CurrentScene = scene;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//ImGui::SetNextWindowPos(viewport->GetWorkPos());
	//ImGui::SetNextWindowSize(viewport->GetWorkSize());
	//ImGui::SetNextWindowViewport(viewport->ID);
	//ImGui::Begin("Dockspace", nullptr, window_flags);
	ImGui::Begin("Dockspace");
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(1,0,0,0));
	ImGui::DockSpace(ImGui::GetID("Temp"));
	ImGui::PopStyleColor();
	//ImGui::DockSpace(ImGui::GetID("MyDock"), ImVec2(0,0), dockspace_flags);

	MinColumnWidth = App->GetWindowSize().x * 0.2;
	MaxColumnWidth = App->GetWindowSize().x * 0.3;
	this->SceneTreeEditor();
	this->PropertyEditor(SelectedNode.node);

	ImGui::Begin("Rendering Info");
	ImGui::Text("Frametime\t %.3f ms/f\nFPS\t\t %.1f", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	this->MainMenuBar();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	//glm::vec2 tmpWinSize = Application::ActiveApplication->GetWindowSize();
	//glViewport(LPW, MainMenuBarHeight, tmpWinSize.x - (LPW + RPW), tmpWinSize.y - MainMenuBarHeight);
	//Application::ActiveApplication->SetViewportSize(glm::vec2(tmpWinSize.x - (LPW + RPW), tmpWinSize.y - MainMenuBarHeight));
}

void Editor::MainMenuBar()
{
	static bool ThemeToogleLight = Theme ? 1 : 0;
	static bool ThemeToogleDark = Theme ? 0 : 1;
	
	if (ImGui::BeginMainMenuBar())
	{
		MainMenuBarHeight = ImGui::GetWindowHeight();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", "Alt+F4"))
				App->Exit();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Add"))
			{
				if (SelectedNode.node)
				{
					SelectedNode.node->AddChild(new ColorRect("ColorRect"));
				}
			}
			if (ImGui::MenuItem("Delete"))
			{
				if (SelectedNode.node)
				{
					SelectedNode.node->DeleteSelf();
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Editor"))
		{
			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem("Light", nullptr, &ThemeToogleLight))
					ChangeTheme(1);
				if (ImGui::MenuItem("Dark", nullptr, &ThemeToogleDark))
					ChangeTheme(0);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ThemeToogleLight = Theme ? 1 : 0;
	ThemeToogleDark = Theme ? 0 : 1;;
}

void Editor::SceneTreeEditor()
{
	bool ConfirmationStatus = false;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
	
	ImGui::Begin("Scene Tree", nullptr);

	ImGui::Separator();
	if (ImGui::Button("Add (+)") && SelectedNode.node)
	{
		ImGui::OpenPopup("Node Spawner");
	}
	if (SelectedNode.node)
		NodeSpawner(SelectedNode.node);

	ImGui::SameLine();
	if (ImGui::Button("Remove") && SelectedNode.node)
	{
		ImGui::OpenPopup("Confirm Action");
	}
	if (SelectedNode.node)
		ConfirmationStatus = ConfirmDialog("Delete " + SelectedNode.node->GetNodeName() + " ?");
	if (ConfirmationStatus)
		SelectedNode.node->DeleteSelf();

	ImGui::SameLine();
	char SearchBar[128] = "Search Nodes";
	ImGui::PushItemWidth(-1);
	ImGui::InputText("Search Nodes", SearchBar, IM_ARRAYSIZE(SearchBar));
	ImGui::PopItemWidth();
	ImGui::Separator();

	SelectedNode.SelectedNodeIndex = -1;
	SelectedNode.LoopIndex = -1;

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	DrawTreeStructure(CurrentScene->GetSceneRoot());

	if (SelectedNode.SelectedNodeIndex != -1)
	{
		//Implement Vector for multi select objects, and show property for Vec[0]
		if (ImGui::GetIO().KeyCtrl)
			SelectedNode.selection_mask ^= (1 << SelectedNode.SelectedNodeIndex);
		else
			SelectedNode.selection_mask = (1 << SelectedNode.SelectedNodeIndex);
	}

	//ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::End();
}

void Editor::PropertyEditor(Node* node)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

	ImGui::Begin("Property Editor", nullptr);
	if (node)		
		node->PropertyEditor();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::End();
}

bool Editor::ConfirmDialog(const std::string& Message)
{
	bool Status = false;
	if (ImGui::BeginPopupModal("Confirm Action", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(Message.c_str());
		ImGui::Separator();

		if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); Status = true; }
		
		ImGui::SetItemDefaultFocus();

		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); Status = false; }
		ImGui::EndPopup();
	}
	return Status;
}

void Editor::NodeSpawner(Node* Parent)
{
	bool Close = true;
	char SearchBox[128] = "Node Type";

	ImGui::SetNextWindowSize(ImVec2(MinColumnWidth * 2.0f, App->GetWindowSize().y - 400.0f));
	
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
