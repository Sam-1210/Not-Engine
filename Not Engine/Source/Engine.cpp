#include "Engine.h"
#include "Application.h"
#include "Log.h"
#include "Node.h"
#include "ResourceLoader.h"
#include "Scene.h"
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Engine::DelayFix()
{
	CurrentFrame = (float)glfwGetTime();
	DeltaTime = CurrentFrame - LastFrame;
	LastFrame = CurrentFrame;
}

Engine::Engine(const int& EngineID, Application* App)
{
	Parent = App;
	ID = EngineID;
	DefaultScene = 0;
	DeltaTime = 0.0;
	CurrentFrame = 0.0;
	LastFrame = 0.0;
}

Engine::~Engine()
{
}

void Engine::AddScene(std::shared_ptr<Scene> sc)
{
	Scenes.push_back(sc);
	NE_CORE_INFO("Added Scene : " + sc->GetSceneName());
}

void Engine::SaveCurrentScene()
{
	NE_CORE_INFO("Saving Current Scene");
	std::ofstream SceneFile(GetCurrentScene()->GetSceneName() + ".nsc");
	Scene::SaveScene(GetCurrentScene()->GetSceneRoot(), SceneFile);
	SceneFile.close();
	NE_CORE_INFO("Saving Current Scene Finished Successfully.");
}

void Engine::SaveAllScenes()
{
	NE_CORE_INFO("Saving All Scenes");
	for (auto child : Scenes)
	{
		std::ofstream SceneFile(child->GetSceneName() + ".nsc");
		Scene::SaveScene(child->GetSceneRoot(), SceneFile);
		SceneFile.close();
	}
	NE_CORE_INFO("Saving Scenes Finished Successfully.");
}

void Engine::LoadScene(const std::string& Path)
{
	ResouceLoader::LoadScene(Path);
}

void Engine::RemoveScene(const unsigned int& Index)
{
	NE_CORE_INFO("Removed Scene : " + Scenes[Index]->GetSceneName());
	Scenes.erase(Scenes.begin() + Index);
}

void Engine::NewFrame()
{
	this->DelayFix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
}

void Engine::EndFrame()
{
	glfwSwapBuffers(Parent->GetWindowObject());
	glfwPollEvents();
}

void Engine::Process()
{
	if (Scenes[Scenes.size() - 1])
		Scene::ProcessScene(Scenes[Scenes.size() - 1]->GetSceneRoot());
}

void Engine::Update()
{
	if (Scenes[Scenes.size() - 1])
		Scene::UpdateScene(Scenes[Scenes.size() - 1]->GetSceneRoot());
}

void Engine::Render()
{
	if (Scenes[Scenes.size() - 1])
		Scene::RenderScene(Scenes[Scenes.size() - 1]->GetSceneRoot());
}

