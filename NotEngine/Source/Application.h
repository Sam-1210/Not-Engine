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
	Application(const std::string& Name, const int& width, const int& height, const bool& Vsync = true, const std::string& Path = "");
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

