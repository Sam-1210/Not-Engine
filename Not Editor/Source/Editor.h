#pragma once
#include "Node.h"

class Application;
class Scene;
struct SceneTreeSelectedNode;
struct ImFont;
struct ImGuiIO;

class Editor
{
private:
	static Editor* Instance;
	Application* App;
	Scene* CurrentScene;
	float MainMenuBarHeight;
	float MinColumnWidth;
	float MaxColumnWidth;
	float LPW;
	float RPW;
	bool Editable;
	bool Theme;
	bool NodeSpawnerVisiblity;
	ImFont* EditorFont;
	ImGuiIO* io;

	static SceneTreeSelectedNode SelectedNode;
	static void DrawTreeStructure(Node* node);
	Editor(const bool& EditMode, Application* App);
public:
	static Editor* InitialiseEditor(const bool& EditMode, Application* App);
	static Editor* GetInstance();
	~Editor();

	float GetMainMenuBarHeight();
	float GetLeftPanelWidth();
	float GetRightPanelWidth();
	void SetContext(Application* ApplicationContext);
	void SetEditMode(const bool& EditMode);
	void ChangeTheme(const bool& Theme);

	void Frame(Scene* scene);
	void MainMenuBar();
	void SceneTreeEditor();
	void PropertyEditor(Node* node);

	//------- Various UI/UX Elements --------------
	bool ConfirmDialog(const std::string& Message);
	void NodeSpawner(Node* Parent);
};
