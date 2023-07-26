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

	bossCirno->SetPlayer(player);
	player->SetBoss(bossCirno);

	LoadGameSceneResource();
	SettingText();

	shape.setSize({ 650.f, 100.f });
	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(sf::Color::Color(255, 255, 255, 0));
	shape.setOutlineThickness(5);
	Utils::SetOrigin(shape, Origins::ML);
	shape.setPosition({ -450.f,200.f });

	hpBar.setFillColor(sf::Color::Yellow);
	hpBar.setPosition({ gameWallSize.x,gameWallSize.y - 10.f });
	Utils::SetOrigin(hpBar, Origins::ML);
	hpBarbyX = gameWallSize.x;

	isTalking = true;
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	while (!talking.empty()) talking.pop();

	for (auto go : gameObjects)
	{
		delete go;
	}
	if (music1 != nullptr)
		delete music1;
	if (bossDie != nullptr) delete bossDie;
	if (timeOutSound != nullptr) delete timeOutSound;
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);

	

	boombCountSpriteCurrent = -1;
	playerLifeSpriteCurrent = 2;
	for (int i = 0;i < 2;++i)
	{
		playerLifeSprite[i]->SetActive(true);
	}

	int boombCountSpriteCurrent = 0;
	int maxBoombCountSpritecurretn = 5;
	for (int i = 0;i < maxBoombCountSpritecurretn;++i)
	{
		boombCountSprite[i]->SetActive(false);
	}

	music1->sound.setVolume(15.f);
	music1->SoundPlay();


	gameTimer = 90.f;
	timeOut = true;
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

	BossEffectSetting();

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

	PlayerStatusSetting();
	BossHpBarSet();
	GameOver();


	if (isTalking && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		if (talkCount % 2 == 0 && !talking.empty())
		{
			talk->text.setFillColor(sf::Color::Red);
			cirnoTalking->SetActive(false);
			playerTalking->SetActive(true);
		}
		else if (talkCount % 2 == 1 && !talking.empty())
		{
			talk->text.setFillColor(sf::Color::Blue);
			cirnoTalking->SetActive(true);
			playerTalking->SetActive(false);
		}
		if (talking.empty())
		{
			isTalking = false;
		}
		else
		{
			talkCount++;
			if (talkCount == 1) cirnoTalking->sprite.setTextureRect({ 130,14,126,242 });
			std::wstring tex = talking.front();
			talk->text.setString(tex);
			talking.pop();
		}
	}
	else if (!isTalking)
	{
		gameTimer -= dt;
		Scene::Update(dt);
		cirnoTalking->SetActive(isTalking);
		talk->SetActive(isTalking);
	}
	SetTextGoByTexture();

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		GamePlaySettingReset();
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
	window.setView(worldView);
	window.draw(hpBar);
	if (isTalking)
	{
		window.draw(shape);
	}

}

void SceneGame::DecreasePlayerLife()
{
	playerLifeSpriteCurrent--;
	if (playerLifeSpriteCurrent < 0) playerLifeSpriteCurrent = 0; 
	this->playerLifeSprite[playerLifeSpriteCurrent]->SetActive(false);

}

void SceneGame::IncreasePlayerLife()
{
	playerLifeSprite[playerLifeSpriteCurrent ++]->SetActive(true);
}

void SceneGame::UseBoomb()
{
	if (boombCountSpriteCurrent < 0) return;
	boombCountSprite[boombCountSpriteCurrent--]->SetActive(false);
}

void SceneGame::SettingText()
{
	bossName = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	bossName->text.setCharacterSize(30);
	bossName->text.setString("Name : Cirno");
	bossName->text.setOutlineThickness(3);
	bossName->text.setOutlineColor(sf::Color::White);
	bossName->text.setFillColor(sf::Color::Blue);
	bossName->SetOrigin(Origins::ML);
	bossName->SetPosition(gameWallSize.x, gameWallSize.y - 30.f);


	gameTimeText = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	gameTimeText->text.setCharacterSize(10);
	gameTimeText->text.setString("Time :");
	gameTimeText->text.setOutlineThickness(3);
	gameTimeText->text.setOutlineColor(sf::Color::Black);
	gameTimeText->SetPosition(0.f, gameWallSize.y - 30.f);

	scoreBys = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	scoreBys->sprite.setTextureRect({ 217, 32, 10, 11 });
	scoreBys->SetScale(2.0f, 2.0f);
	scoreBys->SetPosition(280.f, -250.f);

	scoreByc = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	scoreByc->sprite.setTextureRect({ 190,49,8,8 });
	scoreByc->SetScale(2.0f, 2.0f);
	scoreByc->SetPosition(300.f, -245.f);

	scoreByo = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	scoreByo->sprite.setTextureRect({ 105,63,10,8 });
	scoreByo->SetScale(2.0f, 2.0f);
	scoreByo->SetPosition(315.f, -245.f);

	scoreByr = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	scoreByr->sprite.setTextureRect({ 148,63,9,8 });
	scoreByr->SetScale(2.0f, 2.0f);
	scoreByr->SetPosition(335.f, -245.f);

	scoreBye = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	scoreBye->sprite.setTextureRect({ 218,49,9,8 });
	scoreBye->SetScale(2.0f, 2.0f);
	scoreBye->SetPosition(355.f, -245.f);

	scoreByClone = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	scoreByClone->sprite.setTextureRect({ 121,21,5,8 });
	scoreByClone->SetScale(2.0f, 2.0f);
	scoreByClone->SetPosition(375.f, -245.f);

	scoreNumber = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	scoreNumber->SetPosition(400.f, -245.0f);
	scoreNumber->text.setCharacterSize(30);

	playerDamageText = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	playerDamageText->SetOrigin(Origins::ML);
	playerDamageText->SetPosition(280.f, 0.0f);
	playerDamageText->text.setCharacterSize(30);
	playerDamageText->text.setString("Power :");
	playerDamageText->text.setOutlineThickness(5);
	playerDamageText->text.setOutlineColor(sf::Color::Green);

	playerLife = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	playerLife->SetOrigin(Origins::ML);
	playerLife->SetPosition(280.f, -150.0f);
	playerLife->text.setCharacterSize(30);
	playerLife->text.setString("Player :");
	playerLife->text.setOutlineThickness(5);
	playerLife->text.setOutlineColor(sf::Color::Green);


	for (int i = 0;i < 2;++i)
	{
		playerLifeSprite[i] = (SpriteGo*)AddGo(new SpriteGo("graphics/TouhuoPlayerShoot.png"));
		playerLifeSprite[i]->sprite.setTextureRect({ 318,276,62,60 });
		playerLifeSprite[i]->SetPosition(395.f + (80.f * i), -180.f);
	}

	boombCount = (TextGo*)AddGo(new TextGo("fonts/THE Nakseo.ttf"));
	boombCount->SetOrigin(Origins::ML);
	boombCount->SetPosition(280.f, -50.0f);
	boombCount->text.setCharacterSize(30);
	boombCount->text.setString("Boomb :");
	boombCount->text.setOutlineThickness(5);
	boombCount->text.setOutlineColor(sf::Color::Red);

	for (int i = 0;i < maxBoombCountSpritecurretn;++i)
	{
		boombCountSprite[i] = (SpriteGo*)AddGo(new SpriteGo("graphics/TouhuoPlayerShoot.png"));
		boombCountSprite[i]->sprite.setTextureRect({ 318,276,62,60 });
		boombCountSprite[i]->SetScale(0.5f, 0.5f);
		boombCountSprite[i]->SetPosition(395.f + (30.f * i), -60.f);
		boombCountSprite[i]->sprite.setColor(sf::Color::White);
		boombCountSprite[i]->SetActive(false);
	}

	talking.push(L"���� �Ҵ� ��, ���� �����̾�");
	talking.push(L"�� �׷�? �׷� �ȳ����ٷ�?\n�� �ֺ��� ���� �־��� �ɷ� �ƴµ�?");
	talking.push(L"���, ������ ��������.\n�� �տ� ������ �ִ� �� �˰� �ִ°ž� ? ");
	talking.push(L"ǥ��? �̰� ���~");
	talking.push(L"��ұ��!\n�� ������ ���� ����� ����\n�õ��������ְھ�!!");

	talk = (TextGo*)AddGo(new TextGo("fonts/neodgm.ttf"));
	talk->text.setCharacterSize(30);
	std::wstring tex = talking.front();
	talk->text.setString(tex);
	talking.pop();
	talk->SetOrigin(Origins::ML);
	talk->text.setFillColor(sf::Color::Blue);
	talk->SetPosition(-450.f, 150.f);

}

void SceneGame::LoadGameSceneResource()
{
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

	cirnoTalking = (SpriteGo*)AddGo(new SpriteGo("graphics/cirnoFace.png"));
	cirnoTalking->sprite.setTextureRect({ 0,12,127,244 });
	cirnoTalking->SetPosition(gameWallSize.x, FRAMEWORK.GetWindowSize().y * 0.2f);
	cirnoTalking->SetOrigin(Origins::ML);

	playerTalking = (SpriteGo*)AddGo(new SpriteGo("graphics/PlaterFace.png"));
	playerTalking->sprite.setTextureRect({ 0,12,127,244 });
	playerTalking->SetPosition(gameWallSize.x, FRAMEWORK.GetWindowSize().y * 0.2f);
	playerTalking->SetOrigin(Origins::ML);
	playerTalking->SetActive(false);

	gameOver = (SpriteGo*)AddGo(new SpriteGo("graphics/touhou_font.png"));
	gameOver->sprite.setTextureRect({ 150,196,30,9 });
	gameOver->SetPosition(-160.f, 0);
	gameOver->SetActive(false);
	gameOver->SetOrigin(Origins::MC);
	gameOver->SetScale(5.f, 5.f);
	gameOver->sortLayer = 1;

	bossEffect = (SpriteGo*)AddGo(new SpriteGo("graphics/Boss.png"));
	bossEffect->sprite.setTextureRect({ 609,1182,125,122 });
	bossEffect->sortLayer = -1;
	bossEffect->SetOrigin(Origins::MC);
	bossEffect->SetActive(false);

	music1 = new SoundGo("Sounds/ġ������-����Ʈ-���-����-Ǯ����.wav");
	bossDie = new SoundGo("Sounds/BossDie.wav");
	timeOutSound = new SoundGo("Sounds/timeout.wav");
}

void SceneGame::GamePlaySettingReset()
{
	player->Reset();
	bossCirno->Reset();
	gameOver->SetActive(false);
	gameTimer = 90.f;
	playerLifeSpriteCurrent = 2;
	boombCountSpriteCurrent = -1;
	for (int i = 0;i < 2;++i)
	{
		playerLifeSprite[i]->SetActive(true);
		
	}
	for (int i = 0;i < maxBoombCountSpritecurretn;++i)
	{
		boombCountSprite[i]->SetActive(false);
	}
}

void SceneGame::GameOver()
{
	if (player->GetPlayerDie())
	{
		gameOver->SetActive(player->GetPlayerDie());
		gameTimer = 0.f;
	}
	if (gameTimer <= 0.f && !player->GetPlayerDie())
	{
		player->SetPlayerDie(true);
		timeOutSound->SoundPlay();
	}
	if (player->GetPlayerDie() && INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
	{
		GamePlaySettingReset();
	}
}

void SceneGame::BossEffectSetting()
{
	bossEffect->SetPosition(bossCirno->GetPosition());

	if (bossCirno->GetBossStop())
	{
		bossEffect->SetActive(true);
	}
	else
	{
		bossEffect->SetActive(false);
	}
	bossEffect->SetActive(bossCirno->GetBossStop());
}

void SceneGame::PlayerStatusSetting()
{
	int hp = bossCirno->GetBossHp();
	if (hp % 50 == 0 && !getBoomb)
	{
		randStatus = Utils::RandomRange(0, 3);
		if (randStatus == 0)
		{
			boombCountSpriteCurrent++;
			if (boombCountSpriteCurrent >= 5) return;
			boombCountSprite[boombCountSpriteCurrent]->SetActive(true);
		}
		else if (player->GetPlayerDamage() <= 5.f && randStatus == 2) player->IncreaseDamage();
		getBoomb = true;
	}
	else if (hp % 50 != 0) getBoomb = false;

	if (hp % 100 == 0 && !getPlayerLife && (player->GetPlayerLife() < 2) && player->GetPlayerLife() > 0)
	{
		randStatus = Utils::RandomRange(0, 4);
		if (randStatus == 0)
		{
			IncreasePlayerLife();
			player->IncreasePlayerLife();
		}
	}
}

void SceneGame::BossHpBarSet()
{
	if (bossCirno->GetBossDie())
	{
		bossDie->SoundPlay();
		music1->SoundStop();
		SCENE_MGR.ChangeScene(SceneId::Ending);
		hpBar.setSize({ 0.f, 5.f });
	}
	else hpBar.setSize({ bossCirno->GetBossHp(), 5.f });
}

void SceneGame::SetTextGoByTexture()
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num0))
	{
		std::cout << scoreNumber->text.getOrigin().x<<"//"<< scoreNumber->text.getOrigin().y << std::endl;
	}


	if (gameTimer <= 0.f) gameTimer = 0.f;
	std::stringstream timerstr;
	timerstr << "Time :" << gameTimer;
	gameTimeText->text.setString(timerstr.str());

	std::stringstream stream;
	stream << std::setw(5) << std::setfill('0') << bossCirno->GetScore();
	scoreNumber->text.setString(stream.str());
	scoreNumber->SetOrigin(Origins::ML);

	std::stringstream damagestream;
	damagestream << "Power : " << player->GetPlayerDamage();
	playerDamageText->text.setString(damagestream.str());


}
