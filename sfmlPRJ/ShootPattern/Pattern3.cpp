#include "stdafx.h"
#include "Pattern3.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Boss.h"
Pattern3::Pattern3()
{
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		//bullet->SetBoss(boss);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
}

void Pattern3::ShootBullets()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	float minFrequency = 2.f;
	float maxFrequency = 50.f;
	float amplitude = 100.f;
	Shoot* shoot = bossShootPool.Get();
	shoot->SetPlayer(player);

	sf::Vector2f playerPosition = player->GetPosition();
	sf::Vector2f shootDirection = playerPosition - boss->GetPosition();
	float angle = Utils::Angle(shootDirection.y, playerPosition.x);
	float frequency = minFrequency + static_cast<float>(1) / (maxFrequency - minFrequency);


	shoot->SetPattenInfo(Shoot::NoramalPatten::FrequencyType, boss->GetPosition(), angle, "BossNormalShooting1", minFrequency, maxFrequency);
	shoot->SetWallBounds(wallBounds, imgWidth, imgHeight);
	shoot->sortLayer = -1;
	if (sceneGame != nullptr)
	{
		sceneGame->AddGo(shoot);
	}
}

void Pattern3::Update(float dt)
{
}

void Pattern3::SetWallBounds(sf::Vector2f pos, float width, float height)
{
	wallBounds = pos;
	imgWidth = width;
	imgHeight = height;
}
