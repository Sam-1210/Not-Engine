#pragma once
#include "Node2D.h"
#include "Node3D.h"
#include <fstream>

class Camera;

class Scene
{
protected:
	Node* SceneRoot;
	Camera* mSceneCamera;
	std::string SceneName;

public:
	Scene(const std::string& _SceneName);
	~Scene();

	void Load(std::ifstream& SceneFile);

	inline Node* GetSceneRoot() { return this->SceneRoot; }
	inline Camera* GetSceneCamera() { return mSceneCamera; }
	inline std::string GetSceneName() const { return this->SceneName; }
	inline void RenameScene(std::string&& NewName) { SceneRoot->Rename(std::move(NewName)); }

	static void SaveScene(Node* node, std::ofstream& SceneFile);
	static void ProcessScene(Node* node);
	static void UpdateScene(Node* node, Camera* SceneCam);
	static void RenderScene(Node* node);
};
