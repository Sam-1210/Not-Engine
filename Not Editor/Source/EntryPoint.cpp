#include "Not Engine.h"
#include <Windows.h>

int main()
{
	/* To Do:
	1. icon
	5. Childerns Transformations Relative to Parents
	11. Context menu
	12. object highlighting
	13. Gizmo
	14. change type of node (cast to other types)
	15. animation player
	16. all engine file data to be stored within engine as strings and pushed to disk whenever those files are missing
	16.a. or use archives to store that data
	17. Render viewport on a texture in editor
	18. Objects to have mvp in pixels instead of [-1.0,1.0]
	19. Event Manager
	20. texture flags
	21. "View" menu in mainmenu bar
	22. Signal system via function ptrs, each class have set of signals which are null function ptr, user sets it,
	and if values aren't null then they are called by member function in case of events
	23. user functions are separate cpp which will be compiled with main application when dev starts application from engine.
	24. viewport 2d and viewport 3d
	25.
	*/
	Application* myApp = new Application("AppDebug", glm::vec2(1280, 720), glm::vec2(320, 180),
		glm::vec2(4, 4), true, true, false, WrapperEnum::Mode_Windowed, false);
	MyStatus status = myApp->Init();

	if (status != MyStatus::Init_Success)
		return (int)status;
	Engine* eg = myApp->GetEngine();
	Node2D* rect = new ColorRect("Red Square", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Node2D* rect1 = new ColorRect("Green Square", glm::vec4(0.0f, 1.0f, 0.0f, 0.6f));
	Node2D* rect2 = new ColorRect("Blue Square", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	rect->SetPosition(glm::vec2(0.0f, 0.0f));
	rect->SetScale(2.0f, 2.0f);
	rect1->SetScale(0.5f, 0.5f);
	rect2->SetScale(0.25f, 0.25f);

	Scene* newScene = new Scene("Scene 1");
	eg->AddScene(newScene);
	Node* root = newScene->GetSceneRoot();
	root->AddChild(rect);
	rect->AddChild(rect2);
	root->AddChild(rect1);
	root->AddChild(new TextureRect("Logo", EnginePath::TextureFolder + "NotEngine.jpg"));

	while (myApp->WindowIsNotClosed())
	{
		eg->NewFrame();
		eg->Process();
		eg->Update();
		eg->Render();
		eg->EndFrame();
	}

	delete myApp;
	return 0;
}