#include "Application.h"
#include "Log.h"
#include "ResourceLoader.h"
#include "Scene.h"

Application::Application(const std::string& Name, const int& width, const int& height, const bool& Vsync, const std::string& Path)
	:WindowLayer(Name, width, height, Vsync, Path)
{
	OpenGL::Core::LoadGL();
	DefaultScene = -1;
	CurrentScene = -1;
}

Application::~Application()
{
}

void Application::AddScene(std::shared_ptr<Scene> sc)
{
	Scenes.push_back(sc);
	NE_CORE_INFO("Added Scene : " + sc->GetSceneName());
	CurrentScene++; //----------------------------------------------------------------tmppppp
}

void Application::RemoveScene(const unsigned int& Index)
{
	NE_CORE_INFO("Removed Scene : " + Scenes[Index]->GetSceneName());
	Scenes.erase(Scenes.begin() + Index);
}

void Application::Ready()
{
	OpenGL::Core::ClearBufferBits(OpenGL::Enums::ColorBit | OpenGL::Enums::DepthBit);
	OpenGL::Core::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Application::Process()
{
	if (Scenes[Scenes.size() - 1])
		Scene::ProcessScene(Scenes[CurrentScene]->GetSceneRoot());
}

void Application::Update()
{
	if (Scenes[Scenes.size() - 1])
		Scene::UpdateScene(Scenes[CurrentScene]->GetSceneRoot());
}

void Application::Render()
{
	if (Scenes[Scenes.size() - 1])
		Scene::RenderScene(Scenes[CurrentScene]->GetSceneRoot());
}

void Application::MainLoop()
{
	while (isOpen())
	{
		Ready();
		PollEvents();
		Process();
		Update();
		Render();
		SwapBuffers();
	}
}

void Application::SaveCurrentScene()
{
	NE_CORE_INFO("Saving Current Scene");
	std::ofstream SceneFile("./Assets/Scenes/" + GetCurrentScene()->GetSceneName() + ".nsc");
	Scene::SaveScene(GetCurrentScene()->GetSceneRoot(), SceneFile);
	SceneFile.close();
	NE_CORE_INFO("Saving Current Scene Finished Successfully.");
}

void Application::SaveAllScenes()
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

void Application::LoadScene(const std::string& Path)
{
	ResouceLoader::LoadScene(Path);
}
