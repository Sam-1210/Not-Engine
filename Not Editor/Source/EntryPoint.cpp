#include <Not Engine.h>
#include <Windows.h>
#include "Editor.h"
#include "DemoScene.h"
#include <FrameBuffer.h>

int main()
{
	/* TODO:
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
	25. window resize issue signal to engine for update matrices
	26. optimise framebuffer class
	27. handle editor class members, organisse and clean code.
	*/
	Application* EditorApp = new Application("Not Editor", glm::vec2(1280, 720), glm::vec2(320, 180),
		glm::vec2(4, 6), true, true, false, WrapperEnum::Mode_Windowed, false);

	MyStatus status = EditorApp->Init();

	if (status != MyStatus::Init_Success)
		return (int)status;

	Editor* editor = Editor::InitialiseEditor(true, EditorApp);
	Engine* eg = EditorApp->GetEngine();

	DemoScene(eg);

	while (EditorApp->WindowIsNotClosed())
	{
		editor->EditorTmp();
		eg->NewFrame();
		eg->Process();
		eg->Update();
		eg->Render();
		editor->Frame(eg->GetCurrentScene());
		
		eg->EndFrame();
	}

	delete EditorApp;
	return 0;
}