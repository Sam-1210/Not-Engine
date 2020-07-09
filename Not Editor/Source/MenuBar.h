#pragma once
#include "EditorComponents.h"
#include "MiscStructs.h"

class MenuBar : public EditorComponents
{
private:
	//MenuFlags flags;
public:
	MenuBar(NotEditor* Parent);
	~MenuBar();
	void Ready() override;
	void Render() override;
};
