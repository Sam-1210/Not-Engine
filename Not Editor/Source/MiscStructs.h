#pragma once

class Scene;
class Node;

struct Panel
{
	bool visible;
	unsigned int width;
	unsigned int height;
	//Imguiwindowflags flags;
};

struct SelectedNode
{
	bool isSelected;
	int selection_mask;
	int LoopIndex;
	int SelectedNodeIndex;
	Node* node;
};