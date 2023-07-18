#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "Boss.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"
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
	background->SetPosition(-FRAMEWORK.GetWindowSize() * 0.5f);

	gameBackground = (SpriteGo*)AddGo(new SpriteGo("graphics/GamePlayBackGround.png", "GameBackground"));
	gameBackground->sortLayer = -1;
	gameBackground->sortOrder = 0;
	gameBackground->SetOrigin(Origins::TL);
	gameBackground->SetScale(0.9f, 1.f);
	gameWallSize = { -FRAMEWORK.GetWindowSize().x * 0.5f + 50.f, -FRAMEWORK.GetWindowSize().y * 0.5f + 60.f };
	gameBackground->SetPosition(gameWallSize);

	miniUi = (SpriteGo*)AddGo(new SpriteGo("graphics/GameName.png", "miniUi"));
	miniUi->SetOrigin(Origins::MC);
	miniUi->SetPosition(FRAMEWORK.GetWindowSize().x * 0.35f, FRAMEWORK.GetWindowSize().y * 0.25f);
	miniUi->sortLayer = -2;

	titleNameHong = (SpriteGo*)AddGo(new SpriteGo("graphics/Hong.png"));
	titleNameHong->sprite.setTextureRect({ 23,11,55,71 });
	titleNameHong->SetPosition(FRAMEWORK.GetWindowSize().x * 0.31f, FRAMEWORK.GetWindowSize().y * 0.2f);
	titleNameHong->sortLayer = -1;


	bossCirno->SetPlayer(player);
	player->SetBoss(bossCirno);

	shape.setSize({gameWallSize.y, 75.f });
	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(sf::Color::Color(255, 255, 255, 0));
	shape.setOutlineThickness(5);
	Utils::SetOrigin(shape, Origins::ML);
	shape.setPosition({-150.f,200.f });

	talk = (TextGo*)AddGo(new TextGo("fonts/neodgm.ttf"));
	talk->text.setCharacterSize(30);
	std::wstring tex = L"나는 바보가 아니다"; //
	talk->text.setString(tex);
	talk->SetOrigin(Origins::ML);
	talk->text.setFillColor(sf::Color::Blue);
	talk->SetPosition(-450.f, 200.f);


	music1 = new SoundGo("Sounds/1Page.wav");
	music1->SoundPlayer();

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
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	isTalking = true;
	cirnoTalking = (SpriteGo*)AddGo(new SpriteGo("graphics/cirnoFace.png"));
	cirnoTalking->sprite.setTextureRect({ 130,14,126,242 });
	cirnoTalking->SetPosition(gameWallSize.x, FRAMEWORK.GetWindowSize().y * 0.2f);
	cirnoTalking->SetOrigin(Origins::ML);


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

	/*frames++;
	frameTime += clock.restart();
	if (frameTime >= sf::seconds(1.0f))
	{
		float fps = frames / frameTime.asSeconds();
		frames = 0;
		frameTime = sf::Time::Zero;
		std::stringstream frameS;
		std::cout << "FPS :" << fps << std::endl; - > 죽여버림 ;;
	}*/

	if (isTalking)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
			isTalking = false;
	}
	else if (!isTalking)
	{
		Scene::Update(dt);
		cirnoTalking->SetActive(isTalking);
		talk->SetActive(isTalking);
	}

	if (music1->sound.getStatus() != sf::Sound::Playing)
	{
		std::cout << "isEnd Sound" << std::endl;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
	
	if (isTalking)
	{
		window.setView(worldView);
		window.draw(shape);
	}
}
