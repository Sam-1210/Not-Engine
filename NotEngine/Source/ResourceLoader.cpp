#include "ResourceLoader.h"
#include "Not Engine.h"


ResouceLoader::ParsedNode ResouceLoader::NodeParser(std::ifstream& SceneFile)
{
	Node* node = nullptr;
	unsigned long long pID = 0;
	std::string type;
	std::string name;

	type = NameParser(SceneFile);
	SceneFile >> pID;
	name = NameParser(SceneFile);

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

Node* ResouceLoader::FindNode(Node* node, unsigned long long& ID)
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

std::string ResouceLoader::NameParser(std::ifstream& SceneFile)
{
	std::string ParsedVar;
	std::string FullVar("");

	SceneFile >> ParsedVar;		//first char is '[', indicates start of block,
	
	if (ParsedVar == "")		//if nothing is read, then it's eof
		return ParsedVar;
	if (ParsedVar != "[")
		NE_CORE_CRITICAL("Scene File is Corrupt.");

	SceneFile >> ParsedVar;
	while (ParsedVar != "]")
	{
		FullVar += ParsedVar;
		FullVar += " ";
		SceneFile >> ParsedVar;
	}
	FullVar.pop_back();
	//FullVar[FullVar.size() - 1] = '\0';	// Removes white space at the end of parsedvar
	return FullVar;
}

std::shared_ptr<Scene> ResouceLoader::LoadScene(const std::string& Path)
{
	// Scene File Format : NodeType ParentID NodeName NodeID Visible __VA_ARGS_OF_DIFFERENT_NODES__

	NE_CORE_INFO("Loading Scene From : {0}", Path);
	std::ifstream SceneFile(Path);
	std::shared_ptr<Scene> LoadedScene;

	if (SceneFile.is_open())
	{
		std::string SceneName;
		SceneName = NameParser(SceneFile); //first word is type, which doesn't matter as of now for Scenes
		//second is Parent ID, which does not exist in case of Scenes
		SceneName = NameParser(SceneFile);

		LoadedScene = std::shared_ptr<Scene>(new Scene(SceneName));
		LoadedScene->Load(SceneFile);

		while(SceneFile.good())
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
