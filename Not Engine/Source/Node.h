#pragma once
#include <string>
#include <vector>
#include "Global.h"

class Node
{
protected:
	bool Visible;
	bool Process;
	Node* Parent;
	std::string Name;
	std::vector<Node*> Childrens;

public:
	/** Creates Node with default name "Node" */
	Node();

	/** Must Provide a Name to Each Node for Identification*/
	Node(const std::string& NodeName);

	/** Must Provide a Name to Each Node for Identification
		Visiblity determines whether to render it.
		isProcess will determine whether Process() to be ticked per frame*/
	Node(const std::string& NodeName, const bool& isVisible, const bool& isProcess = false);

	~Node();

	virtual void PropertyEditor();
	virtual void _process();
	virtual void _update();
	virtual void _render();

	inline bool isVisible() const { return this->Visible; }
	inline void Hide() { this->Visible = false; }
	inline void Show() { this->Visible = true; }

	void Rename(std::string&& NewName);
	void DeleteSelf();
	MyStatus AddChild(Node* node, const bool& AddedFromFile = false);
	MyStatus Duplicate();
	MyStatus MoveDown(const unsigned int& steps);
	MyStatus MoveUp(const unsigned int& steps);
	MyStatus RemoveChild(const std::string& ChildName);
	MyStatus Reparent(Node* NewParent);

	inline unsigned int GetChildrenCount() { return this->Childrens.size(); }
	inline Node* GetChild(const unsigned int& Index) const { return this->Childrens[Index]; }
	inline std::string GetNodeName() const { return this->Name; }
	inline std::vector<Node*>& GetChildrens() { return this->Childrens; }

	Node* GetChild(const std::string& ChildName) const;
	Node* GetParent() const;
	std::string GetParentName() const;
	std::string GetChildName(const unsigned int& Index) const;
	std::string GetChildernNames() const;
};
