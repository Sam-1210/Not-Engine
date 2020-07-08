#include "MenuBar.h"
#include "NotEditor.h"
#include <Application.h>
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
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", "Alt+F4"))
				mParent->GetApp()->Exit();
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
		if (ImGui::BeginMenu("Editor"))
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
