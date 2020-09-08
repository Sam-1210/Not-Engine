#include "NotEditor.h"

#include "ConfirmDialogue.h"
#include "Inspector.h"
#include "MenuBar.h"
#include "NodeSpawner.h"
#include "Profilers.h"
#include "SceneTree.h"
#include "Viewport.h"

#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Not Engine.h>

#include "DemoScene.h"



NotEditor::NotEditor()
{
	this->Theme = 1;
	this->mSelection.selection_mask = 0;
	this->mSelection.node = nullptr;
	LoadEditor();
}

NotEditor::~NotEditor()
{
	//-------------save editor conf----------------
	std::ofstream fs("NotEditor.ncnf");
	fs << Theme;
	//-------------------------------------------
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	NE_CORE_INFO("Editor Shutdown");

	delete EditorApp;
}

void NotEditor::ProjectPane()
{
	//LOADS Project Pane, Render it, get project path, and sets mProjectPAth, calls LoadEditor()
}

void NotEditor::LoadEditor()
{
	/*
	Loads Editor
	checks if default scene exist, load it and push to stack
	*/
	if (std::filesystem::exists("NotEditor.ncnf"))
	{
		std::ifstream fs("NotEditor.ncnf");
		fs >> Theme;
	}
	//--------------------------Initialize App------------------------------------------
	EditorApp = new Application("Not Editor", glm::vec2(1280, 720), glm::vec2(320, 180),
		glm::vec2(4, 6), true, false, false, WrapperEnum::Mode_Windowed, false);

	MyStatus status = EditorApp->Init();

	EngineBackend = EditorApp->GetEngine();

	DemoScene(EngineBackend);

	bool setthisanywhereelse = false;
	if (status != MyStatus::Init_Success)
		setthisanywhereelse |= true;

	//----------------------------Set-up IMGUI----------------------------------------
	ImGui::CreateContext();

	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

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

	ChangeTheme(Theme);

	ImGui_ImplGlfw_InitForOpenGL(EditorApp->GetWindowObject(), true);
	ImGui_ImplOpenGL3_Init();

	//------------------------------Initialize Editor Components and Utilities--------------------------------------------

	MainComponents["Inspector"] = std::shared_ptr<EditorComponents>(new Inspector(this));
	MainComponents["MenuBar"] = std::shared_ptr<EditorComponents>(new MenuBar(this));
	MainComponents["Profilers"] = std::shared_ptr<EditorComponents>(new Profilers(this));
	MainComponents["SceneTree"] = std::shared_ptr<EditorComponents>(new SceneTree(this));
	MainComponents["Viewport"] = std::shared_ptr<EditorComponents>(new Viewport(this, 1280, 720));

	UtilityComponents["ConfirmDialogue"] = std::shared_ptr<EditorComponents>(new ConfirmDialogue(this));
	UtilityComponents["NodeSpawner"] = std::shared_ptr<EditorComponents>(new NodeSpawner(this));

	CurrentScene = EngineBackend->GetCurrentScene(); //--------------------------------this one to set according to files
	NE_CORE_INFO("All Processes of Editor Started Successfully");
}

void NotEditor::Ready()
{
	/*
	iterate scenestack, stack size is 0, loads scene menu, else, load all open scenes and set open scene root
	call known components with their parameters and sceneroot
	*/

	for (auto components : MainComponents)
		components.second->Ready();
}

void NotEditor::Render()
{
	static ImGuiWindowFlags dock_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static int count = 0;
	ImGuiID dockspace_id = ImGui::GetID("MyID");
	bool dockSpaceCreated = ImGui::DockBuilderGetNode(dockspace_id) != nullptr;
	if (!dockSpaceCreated)
	{
		ImGui::DockBuilderRemoveNode(dockspace_id);
		ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->GetWorkSize());

		ImGuiID dock_main_id = dockspace_id;
		ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
		ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.30f, NULL, &dock_main_id);
		ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

		ImGui::DockBuilderDockWindow("Heirarchy", dock_id_left);
		ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
		ImGui::DockBuilderDockWindow("Rendering Profiler", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Driver Info", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
		ImGui::DockBuilderFinish(dockspace_id);
	}

	ImGui::SetNextWindowPos(viewport->GetWorkPos());
	ImGui::SetNextWindowSize(viewport->GetWorkSize());
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::Begin("Dockspace", nullptr, dock_flags);
	ImGui::DockSpace(dockspace_id, ImVec2(0, 0));

	for (auto components : MainComponents)
		components.second->Render();

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
}

void NotEditor::EditorLoop()
{
	while (EditorApp->WindowIsNotClosed())
	{
		Ready();
		EngineBackend->NewFrame();
		EngineBackend->Process();
		EngineBackend->Update();
		EngineBackend->Render();
		Render();
		EngineBackend->EndFrame();
	}
}

void NotEditor::ChangeTheme(const bool& Theme)
{
	this->Theme = Theme;
	if (Theme)
		ImGui::StyleColorsLight();
	else
		ImGui::StyleColorsDark();
}
