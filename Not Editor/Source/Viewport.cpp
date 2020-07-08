#include "Viewport.h"
#include "NotEditor.h"
#include <imgui.h>

Viewport::Viewport(NotEditor* Parent, const int& Width, const int& Height)
	: EditorComponents(Parent), mWidth(Width), mHeight(Height), RenderData(Width, Height)
{
}

void Viewport::Ready()
{
	RenderData.Bind();
}

void Viewport::Render()
{
	RenderData.Unbind();

	ImGui::Begin("Viewport");

	ImVec2 ViewportTexSize = ImGui::GetContentRegionAvail();
	
	ImGui::Image((void*)RenderData.GetColorTexture(), ViewportTexSize, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}
