#include "MenuBar.h"
#include "NotEditor.h"
#include <Application.h>
#include <Log.h>
#include <imgui.h>

MenuBar::MenuBar(NotEditor* Parent) : EditorComponents(Parent)
{
}

MenuBar::~MenuBar()
{
}

void MenuBar::Ready()
{
}

void MenuBar::Render()
{
	static bool ThemeToogleLight = mParent->GetTheme() ? 1 : 0;
	static bool ThemeToogleDark = mParent->GetTheme() ? 0 : 1;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("New Scene", "Ctr+N")) {}
			if (ImGui::MenuItem("Open Scene", "Ctr+O")) {}
			if (ImGui::MenuItem("Open Recent")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Save Scene", "Ctr+S")) 
			{
				mParent->GetApp()->SaveCurrentScene();
			}
			if (ImGui::MenuItem("Save All Scene", "Ctr+Alt+S")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Close Scene","Alt+C")) {}
			if (ImGui::MenuItem("Close All Scene", "Alt+Shift+C")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "Alt+F4"))
				mParent->GetApp()->Close();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
			}
			if (ImGui::MenuItem("Redo"))
			{
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Build"))
		{
			if(ImGui::MenuItem("Build & Run"))
			{
				NE_CORE_INFO("Building \"Sandbox.npj\"");
				mParent->GetApp()->SaveCurrentScene();
				NE_CORE_INFO("Build Successfull!!!");
				system("Sandbox\\Sandbox.exe");
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Profilers", nullptr, &mParent->GetComponent("Profilers")->GetFlag_Visible())) { }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem("Light", nullptr, &ThemeToogleLight))
					mParent->ChangeTheme(1);
				if (ImGui::MenuItem("Dark", nullptr, &ThemeToogleDark))
					mParent->ChangeTheme(0);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ThemeToogleLight = mParent->GetTheme() ? 1 : 0;
	ThemeToogleDark = mParent->GetTheme() ? 0 : 1;;
}
