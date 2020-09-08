#include <Not Engine.h>

int main()
{
	Application Sandbox("Sandbox", glm::vec2(1280, 720), glm::vec2(300, 200), glm::vec2(4, 6), false, true, true);
	Sandbox.Init();
	Engine* EngineBackend = Sandbox.GetEngine();
	EngineBackend->AddScene(ResouceLoader::LoadScene("./Assets/Scenes/Demo Scene.nsc"));

	while (Sandbox.WindowIsNotClosed())
	{
		EngineBackend->NewFrame();
		EngineBackend->Process();
		EngineBackend->Update();
		EngineBackend->Render();
		EngineBackend->EndFrame();
	}
}