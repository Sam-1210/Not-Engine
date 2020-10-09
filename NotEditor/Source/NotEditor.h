#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "MiscStructs.h"

class Application;
class Scene;
class EditorComponents;
struct ImFont;
struct ImGuiIO;

class NotEditor
{
private:
	Application* EditorApp;
	bool Theme;
	ImFont* EditorFont;
	ImGuiIO* io;
	SelectedNode mSelection;
	std::string ProjectPath;
	std::shared_ptr<Scene> CurrentScene;
	std::unordered_map<std::string, std::shared_ptr<EditorComponents>> MainComponents;
	std::unordered_map<std::string, std::shared_ptr<EditorComponents>> UtilityComponents;
	std::unordered_map<std::string, std::shared_ptr<Scene>> SceneStack;
	
public:
	NotEditor();
	~NotEditor();
	void ProjectPane();
	void LoadEditor();
	void Ready();
	void Render();
	void EditorLoop();

	//-----------------------------------------Utility Functions------------------------------------------------------
	void ChangeTheme(const bool& Theme);
	inline Application* GetApp() { return EditorApp; }
	std::shared_ptr<Scene> GetCurrentScene();
	inline bool& GetTheme() { return Theme; }
	inline SelectedNode& GetSelection() { return mSelection; }
	inline std::shared_ptr<EditorComponents> GetComponent(const std::string& ComponentName) { return MainComponents[ComponentName]; }
	inline std::shared_ptr<EditorComponents> GetUtility(const std::string& UtilityName) { return UtilityComponents[UtilityName]; }
	inline std::shared_ptr<Scene> GetActiveScene() { return CurrentScene; }

};