#pragma once
#include "EditorComponents.h"
#include "MiscStructs.h"

class Node;

class SceneTree : public EditorComponents
{
private:
	Panel flags;
	SelectedNode& mSelection;

	void CreateTree(Node* node);
public:
	SceneTree(NotEditor* Parent);
	~SceneTree();
	void Ready() override;
	void Render() override;
};