#pragma once
#include "EditorComponents.h"
#include "MiscStructs.h"

class Profilers : public EditorComponents
{
private:
	Panel flags;
	const char* Vendor;
	const char* Renderer;
	const char* Version;

public:
	Profilers(NotEditor* Parent);
	~Profilers();

	inline bool& GetFlag_Visible() override { return flags.visible; }
	void Ready() override;
	void Render() override;
};
