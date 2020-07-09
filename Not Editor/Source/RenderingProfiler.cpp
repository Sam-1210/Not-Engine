#include "RenderingProfiler.h"
#include "NotEditor.h"
#include <Application.h>
#include <imgui.h>

RenderingProfiler::RenderingProfiler(NotEditor* Parent) 
	: EditorComponents(Parent), flags({true, 0, 0})
{
	Vendor = mParent->GetApp()->GetVendor();
	Renderer = mParent->GetApp()->GetRenderer();
	Version = mParent->GetApp()->GetVersion();
}

RenderingProfiler::~RenderingProfiler()
{
}

void RenderingProfiler::Ready()
{
}

void RenderingProfiler::Render()
{
	if (!flags.visible)
		return;

	ImGui::Begin("Rendering Profiler", &flags.visible);
	flags.width = ImGui::GetWindowSize().x;
	flags.height = ImGui::GetWindowSize().y;

	ImGui::Text("Performance Profiler :\n\n");
	ImGui::Text("Vertices :\t");
	ImGui::Text("Triangles :\t");
	ImGui::Text("Frametime\t %.3f ms/f\nFPS\t\t %.1f", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::Text("\nDriver Info : \n\n");

	ImGui::Text("Vendor :\t"); ImGui::SameLine(); ImGui::Text(Vendor);
	ImGui::Text("Renderer :\t"); ImGui::SameLine(); ImGui::Text(Renderer);
	ImGui::Text("Version :\t"); ImGui::SameLine(); ImGui::Text(Version);
	ImGui::End();
}
