#include "stdafx.h"
#include "Boss.h"
#include "SceneGame.h"
#include "Scene.h"

#include "Player.h"
void Boss::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Move.csv"));


	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);

	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(this);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();

	hitboxShape.setSize({ 32.f, 32.f });
	hitboxShape.setFillColor(sf::Color::Color(255, 255, 255, 0));
	Utils::SetOrigin(hitboxShape, Origins::MC);

	{
		NormalAttackInfo info;
		info.animationClipId = "BossNormalShooting1";
		info.bulletCount = 5;
		info.maxSpeed = 500.f;

		attackInfo.push_back(info);
	}
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
	SetPosition(0.f, -260.f);
}

void Boss::Update(float dt)
{
	BossMove(dt);

	animation.Update(dt);
	SpriteGo::Update(dt);
}

void Boss::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(hitboxShape);
}

void Boss::BossMove(float dt)
{
	testTime -= dt;
	position += direction * speed * dt;
	hitboxShape.setPosition(position);
	SetPosition(position);


	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad0) && testTime < 0.8f)
	{
		testTime = 1.0f;
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		int shootCount = 5;

		for (int count = 0;count < shootCount;++count)
		{

			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);
			sf::Vector2f playerPosition = player->GetPosition();
			sf::Vector2f shootDirection = playerPosition - GetPosition();
			float angle = Utils::Angle(shootDirection.y, playerPosition.x);
			if (count >= 1)
			{

				if (count % 2 == 1)
					angle += Utils::DegreesToRadians(10.0f * (count / 2 + 1)); // 1 2 
				else if (count % 2 == 0)
					angle += Utils::DegreesToRadians(-10.0f * (count / 2)); // 1 2
			}
			shoot->BossNormalFire(position, angle,"BossNormalShooting1");
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad1) && testTime < 0.8f)
	{
		testTime = 1.0f;
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		int shootCount = 6;
		float pattenAngle = 360.f / shootCount;
		for (int count = 0; count < shootCount; ++count)
		{
			Shoot* shoot = bossShootPool.Get();
			shoot->SetPlayer(player);

			float additionalAngle = pattenAngle * count;
			shoot->BossNormalFirePatten1(position, additionalAngle,"BossNormalShooting2");
			shoot->sortLayer = -1;
			if (sceneGame != nullptr)
			{
				sceneGame->AddGo(shoot);
			}
		}
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0) && !hitboxDraw)
	{
		hitboxShape.setFillColor(sf::Color::Color(255, 255, 255, 0));
		hitboxDraw = false;
	}
	else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0) && hitboxDraw)
	{
		hitboxShape.setFillColor(sf::Color::Yellow);
		hitboxDraw = true;
	}

}

bool Boss::CheckCollisionWithBullet(const Shoot& bullet)
{
	if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
	{
		std::cout << "isCollied Boss" << std::endl;
		return true;
	}
	return false;
}
