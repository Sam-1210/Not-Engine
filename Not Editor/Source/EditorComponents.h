#pragma once

class NotEditor;

class EditorComponents
{
protected:
	NotEditor* mParent;
public:
	EditorComponents(NotEditor* Parent) : mParent(Parent) { }
	virtual ~EditorComponents() { }

	virtual inline  bool& GetFlag_Visible() { bool Visible = true;  return Visible; }
	virtual void Ready() = 0;
	virtual void Render() = 0;
};
