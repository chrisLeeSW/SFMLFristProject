#include "stdafx.h"
#include "Boss.h"
#include "SceneGame.h"
#include "Scene.h"
void Boss::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Move.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);

	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->textureId = "graphics/ShootingPatten.png";
		sf::IntRect rect = {0,16,16,16 };
		bullet->sprite.setTextureRect(rect);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();

}

void Boss::Release()
{
	SpriteGo::Release();
	bossShootPool.Release();
}

void Boss::Reset()
{
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(0.f, 0.f);
}

void Boss::Update(float dt)
{
	BossMove(dt);

	SpriteGo::Update(dt);
	animation.Update(dt);
}

void Boss::BossMove(float dt)
{

	if (clock.getElapsedTime().asSeconds() >= 10.f)
	{
		std::cout << "Timeover" << std::endl;

		clock.restart();
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad6))
	{
		direction.x = 1.f;
		if(!moveBoss)
		{ 
			moveBoss = true;
			animation.Play("Move");
		}
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad4))
	{
		direction.x = -1.f;
		if (!moveBoss)
		{
			moveBoss = true;
			animation.Play("Move");
			sprite.setScale(-1.f, 1.f);
		}
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad8))
	{
		direction.y = -1.f;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad5))
	{
		direction.y = 1.f;
	}
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}
	position += direction * speed * dt;





	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad6) || INPUT_MGR.GetKeyUp(sf::Keyboard::Numpad4) || INPUT_MGR.GetKey(sf::Keyboard::Numpad8)|| INPUT_MGR.GetKey(sf::Keyboard::Numpad5))
	{
		animation.Play("Idle");
		direction = { 0.f ,0.f};
		moveBoss = false;
		sprite.setScale(1.f, 1.f);
	}
	SetPosition(position);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0))
	{
	
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		Shoot* shoot = bossShootPool.Get();
		shoot->BossFire(GetPosition());
		shoot->sortLayer = -1;
		std::cout << GetPosition().x << std::endl;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad1))
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		Shoot* shoot = bossShootPool.Get();
		sf::IntRect rect = { 0,16*5,16 ,32 };
		shoot->sprite.setTextureRect(rect);
		shoot->BossFire(GetPosition());
		shoot->sortLayer = -1;
		std::cout << GetPosition().x << std::endl;
		if (sceneGame != nullptr)
		{
			sceneGame->AddGo(shoot);
		}
	}
}
