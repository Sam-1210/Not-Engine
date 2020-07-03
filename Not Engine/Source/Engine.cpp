#include "Engine.h"
#include "Application.h"
#include "Log.h"
#include "Node.h"
#include "Scene.h"
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
	for (Scene* s : Scenes)
		delete s;
}

void Engine::AddScene(Scene* s)
{
	Scenes.push_back(s);
	NE_CORE_INFO("Added Scene : " + s->GetSceneName());
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

