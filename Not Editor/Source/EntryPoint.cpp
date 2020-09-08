#include "NotEditor.h"
#include "Log.h"
#include "WindowLayer.h"
#include "GLFW/glfw3.h"

int main()
{
	//ProjectPane::Start();
	//std::string ProjectPath = ProjectPane::GetProjectPath;
	//NotEditor instance(ProjectPath);
	NotEditor instance;
	instance.EditorLoop();
	return 0;
}