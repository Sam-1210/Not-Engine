#include "Scene.h"

Scene::Scene(const std::string& _SceneName)
{
	this->SceneName = _SceneName;
	SceneRoot = new Node(this->SceneName, true, true);
}

Scene::~Scene()
{
	delete SceneRoot;
}

void Scene::ProcessScene(Node* node)
{
	node->_process();
	for (Node* childs : node->GetChildrens())
		ProcessScene(childs);
}

void Scene::UpdateScene(Node* node)
{
	node->_update();
	for (Node* childs : node->GetChildrens())
		UpdateScene(childs);
}

void Scene::RenderScene(Node* node)
{
	if (!node->isVisible())
		return;
	node->_render();
	for (Node* childs : node->GetChildrens())
		RenderScene(childs);
}
