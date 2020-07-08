#include "Viewport.h"
#include "NotEditor.h"
#include <Application.h>
#include <imgui.h>

Viewport::Viewport(NotEditor* Parent, const int& Width, const int& Height)
	: EditorComponents(Parent), mWidth(Width), mHeight(Height), lastWidth(Width), lastHeight(Height),RenderData(Width, Height)
{
}

void Viewport::Ready()
{
	if (lastWidth != mWidth || lastHeight != mHeight )
	{
		mWidth = lastWidth;
		mHeight = lastHeight;
		RenderData.Resize(lastWidth, lastHeight);
		mParent->GetApp()->SetViewportSize(mWidth, mHeight);
	}

	RenderData.Bind();
}

void Viewport::Render()
{
	RenderData.Unbind();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");

	ImVec2 ViewportTexSize = ImGui::GetContentRegionAvail();
	if (ViewportTexSize.x > 0 && ViewportTexSize.y > 0)
	{
		lastWidth = ViewportTexSize.x;
		lastHeight = ViewportTexSize.y;
	}

	ImGui::Image((void*)RenderData.GetColorTexture(), ViewportTexSize, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::PopStyleVar();
	ImGui::End();
}
