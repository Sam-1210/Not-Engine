#pragma once
#include "WindowLayer.h"
#include "OpenGL_Core.h"
#include <memory>
#include <string>
#include <vector>

class Scene;

class Application : public WindowLayer
{
protected:
	int DefaultScene;
	int CurrentScene;
	std::vector<std::shared_ptr<Scene>> Scenes;

public:
	Application(const std::string& Name, int32_t width, int32_t height, bool Vsync = true, WindowModes Mode = ModeWindowed, const std::string& IconPath = "");
	~Application();
	void AddScene(std::shared_ptr<Scene> sc);
	void RemoveScene(const unsigned int& Index);

	void Ready();
	void Process();
	void Update();
	void Render();

	inline std::shared_ptr<Scene> GetCurrentScene() const { return Scenes[CurrentScene]; }

	void MainLoop();

	//---------------implemented by editor, tmp here-------------------------
	
	void SaveCurrentScene();
	void SaveAllScenes();
	void LoadScene(const std::string& Path);
};

