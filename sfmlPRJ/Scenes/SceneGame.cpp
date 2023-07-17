#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "Boss.h"
#include "SpriteGo.h"
SceneGame::SceneGame() : Scene(SceneId::Game)
{

}

void SceneGame::Init()
{
	Release();
	player = (Player*)AddGo(new Player());
	bossCirno = (Boss*)AddGo(new Boss());

	background = (SpriteGo*)AddGo(new SpriteGo("graphics/GameSceneBackGround.png", "Background"));
	background->sortLayer = -3;
	background->SetPosition(-FRAMEWORK.GetWindowSize()*0.5f);

	gameBackground = (SpriteGo*)AddGo(new SpriteGo("graphics/GamePlayBackGround.png", "GameBackground"));
	gameBackground->sortLayer = -1;
	gameBackground->sortOrder = 0;
	gameBackground->SetOrigin(Origins::TL);
	gameBackground->SetScale(0.9f, 1.f);
	gameWallSize = { -FRAMEWORK.GetWindowSize().x * 0.5f + 50.f, -FRAMEWORK.GetWindowSize().y * 0.5f + 60.f };
	gameBackground->SetPosition(gameWallSize);

	miniUi = (SpriteGo*)AddGo(new SpriteGo("graphics/GameName.png", "miniUi"));
	miniUi->SetOrigin(Origins::MC);
	miniUi->SetPosition(FRAMEWORK.GetWindowSize().x*0.35f, FRAMEWORK.GetWindowSize().y * 0.25f);
	miniUi->sortLayer = -2;

	titleNameHong = (SpriteGo*)AddGo(new SpriteGo("graphics/Hong.png"));
	titleNameHong->sprite.setTextureRect({ 143,9,41,46 });
	titleNameHong->SetPosition(FRAMEWORK.GetWindowSize().x * 0.315f, FRAMEWORK.GetWindowSize().y * 0.232f);
	titleNameHong->sortLayer = -1;


	bossCirno->SetPlayer(player);

	player->SetBoss(bossCirno);
	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({0,0});

	uiView.setSize(size);
	//uiView.setCenter(size * 0.5f);
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	player->SetWallBounds(gameWallSize, gameBackground->sprite.getGlobalBounds().width, gameBackground->sprite.getGlobalBounds().height);
	bossCirno->SetWallBounds(gameWallSize, gameBackground->sprite.getGlobalBounds().width, gameBackground->sprite.getGlobalBounds().height);

	frames++;
	frameTime += clock.restart();
	if (frameTime >= sf::seconds(1.0f))
	{
		float fps = frames / frameTime.asSeconds();
		frames = 0;
		frameTime = sf::Time::Zero;
		std::stringstream frameS;
		std::cout << "FPS :" << fps << std::endl;
	}

	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
