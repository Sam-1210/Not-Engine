#pragma once
#include <memory>
#include <string>
#include <vector>

class Application;
class Scene;

class Engine
{
protected:
	Application* Parent;
	int ID;
	double DeltaTime;
	double CurrentFrame;
	double LastFrame;
	
	unsigned int DefaultScene;
	std::vector<std::shared_ptr<Scene>> Scenes;

	virtual void DelayFix();
public:
	Engine(const int& ID, Application* App);
	~Engine();
	
	inline std::shared_ptr<Scene> GetCurrentScene() const { return Scenes[Scenes.size() - 1];  }

	virtual void AddScene(std::shared_ptr<Scene> sc);
	virtual void SaveCurrentScene();
	virtual void SaveAllScenes();
	virtual void LoadScene(const std::string& Path);
	virtual void RemoveScene(const unsigned int& Index);

	virtual void NewFrame();
	virtual void EndFrame();

	virtual void Process();
	virtual void Update();
	virtual void Render();
};