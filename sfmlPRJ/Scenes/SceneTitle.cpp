#include "stdafx.h"
#include "SceneTitle.h"
#include "Framework/Framework.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"

SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	
}

void SceneTitle::Init() 
{
	Release();
	LoadResourceAndSetting();

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
	
	titleSound->SoundPlay();
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	HandleSceneSelection();
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::LoadResourceAndSetting()
{
	const sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	const sf::Vector2f centerOffset = windowSize * 0.5f;

	const std::string backgroundTexturePath = "graphics/MainTitleGame.png";
	const std::string titleSoundPath = "Sounds/TitleGameSound.wav";
	const std::string fontPath = "fonts/THE Nakseo.ttf";

	
	backGroundGame = (SpriteGo*)AddGo(new SpriteGo(backgroundTexturePath));
	backGroundGame->SetPosition(-centerOffset);

	
	titleSound = new SoundGo(titleSoundPath);

	
	gameSceneText = (TextGo*)AddGo(new TextGo(fontPath));
	gameSceneText->text.setCharacterSize(50);
	gameSceneText->SetOrigin(Origins::MC);
	gameSceneText->SetPosition(380.f, 50.f);
	gameSceneText->text.setString("GamePlay");

	
	rankSceneText = (TextGo*)AddGo(new TextGo(fontPath));
	rankSceneText->text.setCharacterSize(50);
	rankSceneText->SetOrigin(Origins::MC);
	rankSceneText->SetPosition(330.f, 130.f);
	rankSceneText->text.setString("Exit");
}

void SceneTitle::HandleSceneSelection()
{
	sf::Vector2f mousePos = ScreenToWorldPos(INPUT_MGR.GetMousePos());
	if (gameSceneText->text.getGlobalBounds().contains(mousePos))
	{
		gameSceneText->text.setFillColor(sf::Color::Black);
		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			titleSound->SoundStop();
			SCENE_MGR.ChangeScene(SceneId::Game);
			return;
		}
	}
	else if (rankSceneText->text.getGlobalBounds().contains(mousePos))
	{
		rankSceneText->text.setFillColor(sf::Color::Black);
		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			titleSound->SoundStop();
			FRAMEWORK.GetWindow().close();
		}
	}
	else
	{
		gameSceneText->text.setFillColor(sf::Color::White);
		rankSceneText->text.setFillColor(sf::Color::White);
	}
}
