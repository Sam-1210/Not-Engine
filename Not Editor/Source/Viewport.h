#pragma once
#include "EditorComponents.h"
#include <FrameBuffer.h>

class Viewport : public EditorComponents
{
private:
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int lastWidth;
	unsigned int lastHeight;
	FrameBuffer RenderData;
public:
	Viewport(NotEditor* Parent, const int& Width, const int& Height);
	~Viewport() {}

	void Ready() override;
	void Render() override;
};
