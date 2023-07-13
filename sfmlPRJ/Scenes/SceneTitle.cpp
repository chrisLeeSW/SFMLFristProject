#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"
SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	
}

void SceneTitle::Init()
{
	Release();

	backGroundGame = (SpriteGo*)AddGo(new SpriteGo("graphics/GameBackGround.png"));
	backGroundGame->SetPosition(0.f,0.f);
	backGroundGame->SetScale(1.f, 1.5f);
	backGroundGame->sortLayer = -1;

	gameStartText = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf","GameStart"));
	gameStartText->text.setString("GameStart");
	gameStartText->text.setCharacterSize(40);
	gameStartText->SetPosition(FRAMEWORK.GetWindowSize().x *0.4f, FRAMEWORK.GetWindowSize().y * 0.8f);
	gameStartText->SetOrigin(Origins::MC);

	for (auto go : gameObjects)	
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{

		delete go;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	//std::cout << gameStartText->text.getGlobalBounds().height << std::endl;
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
