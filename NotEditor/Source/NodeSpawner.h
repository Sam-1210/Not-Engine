#pragma once
#include "EditorComponents.h"
#include "MiscStructs.h"


class NodeSpawner : public EditorComponents
{
private:
	//MenuFlags flags;
public:
	NodeSpawner(NotEditor* Parent);
	~NodeSpawner();
	void Ready() override;
	void Render() override;
};
