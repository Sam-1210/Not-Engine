#pragma once
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
	std::vector<Scene*> Scenes;

	virtual void DelayFix();
public:
	Engine(const int& ID, Application* App);
	~Engine();
	
	inline Scene* GetCurrentScene() const { return Scenes[Scenes.size() - 1];  }

	virtual void AddScene(Scene* s);
	virtual void RemoveScene(const unsigned int& Index);

	virtual void NewFrame();
	virtual void EndFrame();

	virtual void Process();
	virtual void Update();
	virtual void Render();
};