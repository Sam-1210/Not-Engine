#include "ResourceLoader.h"
#include "Not Engine.h"


ResouceLoader::ParsedNode ResouceLoader::NodeParser(std::ifstream& SceneFile)
{
	Node* node = nullptr;
	unsigned long long pID = 0;
	std::string type;
	std::string name;

	SceneFile >> type;
	SceneFile >> pID;
	SceneFile >> name;

	if (type == "Node")
	{
		node = new Node(name);
		node->Load(SceneFile);
	}
	else if (type == "Node2D")
	{
		node = new Node2D(name);
		node->Load(SceneFile);
	}
	else if (type == "ColorRect")
	{
		node = new ColorRect(name);
		node->Load(SceneFile);
	}
	else if (type == "TextureRect")
	{
		node = new TextureRect(name);
		node->Load(SceneFile);
	}

	return { node, pID };
}

Node* ResouceLoader::FindNode(Node* node, const int& ID)
{
	if (node->GetID() == ID)
		return node;
	Node* found = nullptr;
	for (auto child : node->GetChildrens())
	{
		found = FindNode(child, ID);
		if (found)
			break;
	}
	return found;
}

std::shared_ptr<Scene> ResouceLoader::LoadScene(const std::string& Path)
{
	// Scene File Format : NodeType ParentID NodeName Visible __VA_ARGS_OF_DIFFERENT_NODES__
	NE_CORE_INFO("Loading Scene From : {0}", Path);
	std::ifstream SceneFile(Path);
	std::shared_ptr<Scene> LoadedScene;

	if (SceneFile.is_open())
	{
		std::string SceneName;
		SceneFile >> SceneName; //first word is type, which doesn't matter as of now for Scenes
		//second is Parent ID, which does not exist in case of Scenes
		SceneFile >> SceneName;

		LoadedScene = std::shared_ptr<Scene>(new Scene(SceneName));
		LoadedScene->Load(SceneFile);

		while(!SceneFile.eof())
		{
			ParsedNode pn = NodeParser(SceneFile);
			Node* Parent = FindNode(LoadedScene->GetSceneRoot(), pn.ParentID);
			if (Parent)
				Parent->AddChild(pn.node);
		}

		NE_CORE_INFO("Loading Finished Successfully.");
	}
	else
		NE_CORE_CRITICAL("Failed to Open Scene File.");
	return LoadedScene;
}
