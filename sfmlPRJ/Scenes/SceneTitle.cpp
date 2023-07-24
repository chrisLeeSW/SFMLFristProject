#include "stdafx.h"
#include "SceneTitle.h"
#include "Framework/Framework.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"
SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	
}

void SceneTitle::Init() // 383 MB
{
	Release();
	
	backGroundGame = (SpriteGo*)AddGo(new SpriteGo("graphics/MainTitleGame.png"));
	backGroundGame->SetPosition(-FRAMEWORK.GetWindowSize() * 0.5f);

	titleSound = new SoundGo("Sounds/TitleGameSound.wav");

	gameSceneText=(TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	gameSceneText->text.setCharacterSize(50);
	gameSceneText->SetOrigin(Origins::MC);
	gameSceneText->SetPosition(380.f, 50.f);
	gameSceneText->text.setString("GamePlay");

	rankSceneText = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	rankSceneText->text.setCharacterSize(50);
	rankSceneText->SetOrigin(Origins::MC);
	rankSceneText->SetPosition(330.f,130.f);
	rankSceneText->text.setString("Rank");
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
	if (titleSound != nullptr)
		delete titleSound;
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
	sf::Vector2f mousePos = ScreenToWorldPos(INPUT_MGR.GetMousePos());
	
	if (gameSceneText->text.getGlobalBounds().contains(mousePos))
	{
		gameSceneText->text.setFillColor(sf::Color::Black);
		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			titleSound->SoundStop();
			SCENE_MGR.ChangeScene(SceneId::Game);
		}
	}
	else
	{
		gameSceneText->text.setFillColor(sf::Color::White);
	}
	if (rankSceneText->text.getGlobalBounds().contains(mousePos))
	{
		rankSceneText->text.setFillColor(sf::Color::Black);
		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "rank로가야하지만 아직 구현이 안되어 있음" << std::endl;
			titleSound->SoundStop();
			SCENE_MGR.ChangeScene(SceneId::Game);
		}
	}
	else
	{
		rankSceneText->text.setFillColor(sf::Color::White);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	
	Scene::Draw(window);
}
