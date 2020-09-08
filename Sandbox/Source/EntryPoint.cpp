#include <Not Engine.h>

void Process_in_Script(Node* node)
{
	TextureRect* t = (TextureRect*)node;
	static float i = -1.0f, j = 0.0f;
	t->SetPosition(i, 0.0f);
	if(i < 1.0f)
		i += 0.001f;
	j += 1.0f;
}

void Process2(Node* node)
{
	TextureRect* tmp = (TextureRect*)node;
	static int i = 0; 
	static float j = 0;
	tmp->SetRotation(i--);
	tmp->SetScale(j, j);
	j+=0.001f;
}

int main()
{
	Application Sandbox("Sandbox", 1280, 720);
	std::shared_ptr<Scene> sc = ResouceLoader::LoadScene("./Assets/Scenes/Demo Scene.nsc");
	Sandbox.AddScene(sc);
	Node* Player = sc->GetSceneRoot()->GetChild("Player");
	Node* Friend = sc->GetSceneRoot()->GetChild("Friend");
	Player->SetProcessSignal(&Process_in_Script);
	Friend->SetProcessSignal(&Process2);
	Sandbox.MainLoop();
}