#include "NotEditor.h"
#include "Log.h"
#include "WindowLayer.h"
#include "GLFW/glfw3.h"

int main()
{
	//ProjectPane::Start();
	//std::string ProjectPath = ProjectPane::GetProjectPath;
	//NotEditor instance(ProjectPath);
	NotEditor* instance = new NotEditor();
	instance->EditorLoop();
	Application* app = instance->GetApp();
	delete instance;
	delete app;
	return 0;
}