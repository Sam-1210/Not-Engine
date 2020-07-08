#pragma once
#include "EditorComponents.h"
#include "MiscStructs.h"

class Inspector : public EditorComponents
{
private:
	Panel flags;
	SelectedNode& mSelection;

public:
	Inspector(NotEditor* Parent);
	~Inspector();
	void Ready() override;
	void Render() override;
};