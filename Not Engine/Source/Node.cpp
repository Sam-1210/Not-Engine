#include "Node.h"
#include <sstream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#define ErrNoParentString "There's No Parent for This Node"
#define ErrIndexOutOfBoundsString "Index Out of Bounds"

Node::Node()
{
	this->Name = "Node";
	Visible = true;
	Process = false;
}

Node::Node(const std::string& NodeName)
{
	this->Name = NodeName;
	Visible = true;
	Process = true;
}

Node::Node(const std::string& NodeName, const bool& isVisible, const bool& isProcess)
{
	this->Name = NodeName;
	this->Visible = isVisible;
	this->Process = isProcess;
}

Node::~Node()
{
	for (Node* node : Childrens)
	{
		delete node;
	}
}

void Node::PropertyEditor()
{
	static bool HeaderOpened = true;
	ImGui::SetNextItemOpen(HeaderOpened);
	if (ImGui::CollapsingHeader("Node"))
	{
		std::string tmp = Name;
		if (ImGui::InputText("Name", &tmp, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (tmp.size())
				Rename(std::move(tmp));
			else
				Rename("Unnamed Node");
		}
		ImGui::Checkbox("Visible", &Visible);
		HeaderOpened = true;
	}
	else
		HeaderOpened = false;
}

void Node::_process()
{
}

void Node::_update()
{
}

void Node::_render()
{
}

void Node::Rename(std::string&& NewName)
{
	bool first = true;
	unsigned int Counter = 0;
	if (this->Parent) 
	{
		for (unsigned int i = 0; i < this->Parent->Childrens.size(); i++)
		{
			if (this->Parent->Childrens[i]->Name == NewName)
			{
				if (!first)
					for (int j = Counter; j > 0; j /= 10)
						NewName.pop_back();
				NewName.append(std::to_string(Counter++));
				i = 0;
				first = false;
			}
		}
	}
	this->Name = NewName;
}

void Node::DeleteSelf()
{
	if (Parent)
		Parent->RemoveChild(this->Name);
}

MyStatus Node::AddChild(Node* node, const bool& AddedFromFile)
{
	bool first = true;
	unsigned int counter = 0;

	for (unsigned int i = 0; i < Childrens.size() && !AddedFromFile; i++) 
	{
		if (Childrens[i]->Name == node->Name)
		{
			if (!first)
				for (int j = counter; j > 0; j /= 10)
					node->Name.pop_back();
			node->Name.append(std::to_string(counter++));
			i = 0;
			first = false;
		}
	}

	node->Parent = this;
	this->Childrens.push_back(node);
	return MyStatus::SuccessChildAdded;
}

MyStatus Node::Duplicate()
{
	//Implement Deep Copy
	return MyStatus::ErrException;
}

MyStatus Node::MoveDown(const unsigned int& steps)
{
	return MyStatus::ErrException;
}

MyStatus Node::MoveUp(const unsigned int& steps)
{
	return MyStatus::ErrException;
}

MyStatus Node::RemoveChild(const std::string& ChildName)
{
	for (unsigned int i = 0; i < Childrens.size(); i++)
	{
		if(Childrens[i]->Name == ChildName)
		{
			Childrens[i]->Parent = nullptr;
			Childrens.erase(Childrens.begin() + i);
			return MyStatus::SuccessChildRemove;
		}
	}

	return MyStatus::ErrChildRemove;
}

MyStatus Node::Reparent(Node* NewParent)
{
	Node* CurrentParent = this->Parent;
	MyStatus status = CurrentParent->RemoveChild(this->Name);
	if (status == MyStatus::ErrChildRemove)
	{
		return MyStatus::ErrException;
	}
	status = NewParent->AddChild(this);
	
	return MyStatus::SuccessReparent;
}

Node* Node::GetParent() const
{
	return Parent;
}

std::string Node::GetParentName() const
{
	if(!Parent)
		return ErrNoParentString;
	return Parent->Name;
}

Node* Node::GetChild(const std::string& ChildName) const
{
	for (Node* child : Childrens)
	{
		if (child->Name == ChildName)
			return child;
	}
	return nullptr;
}

std::string Node::GetChildName(const unsigned int& Index) const
{
	if (Index >= Childrens.size())
		return ErrIndexOutOfBoundsString;
	return Childrens[Index]->Name;
}


std::string Node::GetChildernNames() const
{
	std::stringstream buff;
	for (Node* child : Childrens)
	{
		buff << child->Name << "\n";
	}
	return buff.str();
}
