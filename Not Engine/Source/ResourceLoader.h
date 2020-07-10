#pragma once
#include <fstream>
#include <memory>
#include <string>

class Node;
class Scene;


namespace ResouceLoader
{
	struct ParsedNode
	{
		Node* node;
		unsigned long long ParentID;
	};
	ParsedNode NodeParser(std::ifstream& SceneFile);
	Node* FindNode(Node* node, const int& ID);
	std::shared_ptr<Scene> LoadScene(const std::string& Path);
}
