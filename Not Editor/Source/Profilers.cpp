#include "Profilers.h"
#include "NotEditor.h"
#include <Application.h>
#include <imgui.h>

Profilers::Profilers(NotEditor* Parent)
	: EditorComponents(Parent), flags({true, 0, 0})
{
	Vendor = mParent->GetApp()->GetVendor();
	Renderer = mParent->GetApp()->GetRenderer();
	Version = mParent->GetApp()->GetVersion();
}

Profilers::~Profilers()
{
}

void Profilers::Ready()
{
}

void Profilers::Render()
{
	if (!flags.visible)
		return;

	ImGui::Begin("Rendering Profiler", &flags.visible);
	flags.width = ImGui::GetWindowSize().x;
	flags.height = ImGui::GetWindowSize().y;

	ImGui::Text("Vertices :\t");
	ImGui::Text("Triangles :\t");
	ImGui::Text("Frametime\t %.3f ms/f\nFPS\t\t %.1f", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("Driver Info", &flags.visible);
	ImGui::Text("Vendor :\t"); ImGui::SameLine(); ImGui::Text(Vendor);
	ImGui::Text("Renderer :\t"); ImGui::SameLine(); ImGui::Text(Renderer);
	ImGui::Text("Version :\t"); ImGui::SameLine(); ImGui::Text(Version);
	ImGui::End();
}
