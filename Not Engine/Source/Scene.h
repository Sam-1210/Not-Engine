#pragma once
#include "Node2D.h"
#include "Node3D.h"
#include <fstream>

class Scene
{
protected:
	Node* SceneRoot;
	std::string SceneName;

public:
	Scene(const std::string& _SceneName);
	~Scene();

	void Load(std::ifstream& SceneFile);

	inline Node* GetSceneRoot() { return this->SceneRoot; }
	inline std::string GetSceneName() const { return this->SceneName; }
	inline void RenameScene(std::string&& NewName) { SceneRoot->Rename(std::move(NewName)); }

	static void SaveScene(Node* node, std::ofstream& SceneFile);
	static void ProcessScene(Node* node);
	static void UpdateScene(Node* node);
	static void RenderScene(Node* node);
};
