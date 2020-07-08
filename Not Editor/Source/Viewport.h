#pragma once
#include "EditorComponents.h"
#include <FrameBuffer.h>

class Viewport : public EditorComponents
{
private:
	unsigned int mWidth;
	unsigned int mHeight;
	FrameBuffer RenderData;
public:
	Viewport(NotEditor* Parent, const int& Width, const int& Height);
	~Viewport() {}

	void Ready() override;
	void Render() override;
};
