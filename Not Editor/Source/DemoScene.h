#pragma once
#include <Not Engine.h>
#include <string>

void DemoScene(Engine* eg)
{
	Scene* newScene = new Scene("Testing");
	eg->AddScene(newScene);

	Node* root = newScene->GetSceneRoot();

	Node2D* BG = new TextureRect("BG", EnginePath::TextureFolder + "bg.png");
	Node2D* Player = new TextureRect("Player", EnginePath::TextureFolder + "player.png");
	Node2D* Friend = new TextureRect("Friend", EnginePath::TextureFolder + "friend.png");
	Node2D* Group = new Node2D("Enemies");
	Node2D* Group1 = new Node2D("Wall");

	BG->SetScale(glm::vec2(4.0f, 3.0f));
	Player->SetPosition(-1.0f, 0.0f);
	Player->SetScale(0.5f, 0.5f);
	Friend->SetPosition(-1.0f, -0.5f);
	Friend->SetScale(0.5f, 0.5f);

	root->AddChild(BG);
	root->AddChild(Group);
	root->AddChild(Player);
	root->AddChild(Friend);
	root->AddChild(Group1);

	for (int i = 0; i < 3; i++)
	{
		Node2D* Enemy = new TextureRect("Enemy1", EnginePath::TextureFolder + "enemy" + std::to_string(i) + ".png");
		Enemy->SetScale(0.5f, 0.5f);
		Enemy->SetPosition(1.0f, 0.5f - (0.6f * i));
		Group->AddChild(Enemy);
	}

	for (int i = 0; i < 10; i++)
	{
		Node2D* Box = new ColorRect("Block" + std::to_string(i), glm::vec4(0.3f, 0.13f, 0.01f, 1.0f));
		Box->SetPosition(0.0f, 0.5f - (0.11f * i));
		Box->SetScale(0.1f, 0.1f);
		Group1->AddChild(Box);
	}
	
}