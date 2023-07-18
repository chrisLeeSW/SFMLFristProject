#include "stdafx.h"
#include "SceneTitle.h"
#include "Framework/Framework.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"
SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	resourceListPath = "graphicsTable/GameTitleResource.csv";
}

void SceneTitle::Init()
{
	Release();
	
	backGroundGame = (SpriteGo*)AddGo(new SpriteGo("graphics/MainTitleGame.png"));
	backGroundGame->SetPosition(-FRAMEWORK.GetWindowSize() * 0.5f);

	titleSound = new SoundGo("Sounds/TitleGameSound.wav");
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
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);

	titleSound->SoundPlayer();
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
		titleSound->SoundStop();
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
