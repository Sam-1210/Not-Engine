#include "NotEditor.h"

int main(int argc, char* argv)
{
	/*Boilerplate For Projectpane*/
	//ProjectPane::Start();
	//std::string ProjectPath = ProjectPane::GetProjectPath;
	//NotEditor instance(ProjectPath);
	NotEditor instance;
	instance.EditorLoop();
	return 0;
}